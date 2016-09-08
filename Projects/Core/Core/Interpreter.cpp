
// Header
#include "Interpreter.h"

// Library includes
#include <cassert>
#include <map>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Namespace.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Utils.h>
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Interpreter::Interpreter(SymbolScope *scope)
: mControlFlow(ControlFlow::Normal),
  mOwner(scope),
  mRepository(0)
{
}

Interpreter::~Interpreter()
{
}

/*
 * processes tokens and updates the given result
 */
ControlFlow::E Interpreter::execute(Object *result)
{
	return interpret(mTokens, result);
}

void Interpreter::expression(Object *result, TokenIterator& start)
{
	parseCondition(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::AND &&
			 op != Token::Type::NAND &&
			 op != Token::Type::NOR &&
			 op != Token::Type::OR ) {
			return;
		}

		start++;	// consume operator token

		Object v2;
		parseCondition(&v2, start);

		if ( op == Token::Type::AND && isTrue(*result) ) {
			*result = BoolObject(isTrue(*result) && isTrue(v2));
		}
		else if ( op == Token::Type::NAND && !isTrue(*result) ) {
			*result = BoolObject(!isTrue(*result) && !isTrue(v2));
		}
		else if ( op == Token::Type::NOR && !isTrue(*result) ) {
			*result = BoolObject(!isTrue(*result) || !isTrue(v2));
		}
		else if ( op == Token::Type::OR && !isTrue(*result) ) {
			*result = BoolObject(isTrue(*result) || isTrue(v2));
		}
	}
}

void Interpreter::garbageCollector()
{
	Symbols symbols;
	getScope()->exportSymbols(symbols);

	for ( Symbols::reverse_iterator it = symbols.rbegin(); it != symbols.rend(); ++it ) {
		if ( it->first != IDENTIFIER_BASE && it->first != IDENTIFIER_THIS &&
			 it->second && it->second->getSymbolType() == Symbol::IType::ObjectSymbol ) {
			getRepository()->removeReference(static_cast<Object*>(it->second));
		}
	}
	symbols.clear();
}

const ExceptionData& Interpreter::getExceptionData() const
{
	return mExceptionData;
}

Namespace* Interpreter::getEnclosingSpace() const
{
	IScope* scope = mOwner->getEnclosingScope();

	while ( scope ) {
		IScope* outter = scope->getEnclosingScope();

		if ( !outter || outter->getScopeType() != IScope::IType::MethodScope ) {
			return 0;
		}

		Namespace* result = dynamic_cast<Namespace*>(outter);
		if ( result ) {
			return result;
		}

		scope = outter;
	}

	return 0;
}

Repository* Interpreter::getRepository() const
{
	return mRepository;
}

SymbolScope* Interpreter::getScope() const
{
	if ( !mScopeStack.empty() ) {
		return mScopeStack.back();
	}

	return mOwner;
}

const TokenList& Interpreter::getTokens() const
{
	return mTokenStack.back();
}

inline Symbol* Interpreter::identify(TokenIterator& token) const
{
	Symbol *result = 0;
	bool onlyCurrentScope = false;

	while ( token->type() == Token::Type::IDENTIFER || token->type() == Token::Type::TYPE ) {
		std::string identifier = token->content();

		if ( !result ) {
			result = getScope()->resolve(identifier, onlyCurrentScope);

			if ( !result ) {
				Namespace* space = getEnclosingSpace();
				if ( space ) {
					result = getScope()->resolve(space->QualifiedTypename() + "." + identifier, onlyCurrentScope);
				}
			}
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::BluePrintObjectSymbol:
					result = static_cast<Designtime::BluePrintObject*>(result)->resolve(identifier, onlyCurrentScope);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = static_cast<Namespace*>(result)->resolve(identifier, onlyCurrentScope);
					break;
				case Symbol::IType::ObjectSymbol:
					result = static_cast<Object*>(result)->resolve(identifier, onlyCurrentScope);
					break;
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::MethodSymbol:
					throw Common::Exceptions::NotSupported("cannot directly access locales of blueprint or method");
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol found");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		token++;

		TokenIterator tmp = token;
		tmp++;
		if ( tmp->type() != Token::Type::IDENTIFER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		token++;
	}

	return result;
}

Symbol* Interpreter::identifyMethod(TokenIterator& token, const ParameterList& params) const
{
	Symbol *result = 0;
	bool onlyCurrentScope = false;

	while ( token->type() == Token::Type::IDENTIFER || token->type() == Token::Type::TYPE ) {
		std::string identifier = token->content();

		if ( !result ) {
			result = getScope()->resolve(identifier, onlyCurrentScope);

			// look for an overloaded method
			if ( result && result->getSymbolType() == Symbol::IType::MethodSymbol ) {
				result = static_cast<Method*>(mOwner)->resolveMethod(identifier, params, onlyCurrentScope);
			}
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					result = static_cast<Namespace*>(result)->resolveMethod(identifier, params, onlyCurrentScope);
					break;
				case Symbol::IType::ObjectSymbol:
					result = static_cast<Object*>(result)->resolveMethod(identifier, params, onlyCurrentScope);
					break;
				case Symbol::IType::BluePrintEnumSymbol:
					throw Common::Exceptions::NotSupported("static method usage not supported");
				case Symbol::IType::BluePrintObjectSymbol:
					result = static_cast<Designtime::BluePrintObject*>(result)->resolveMethod(identifier, params, onlyCurrentScope);
					break;
				case Symbol::IType::MethodSymbol:
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol found");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		token++;

		TokenIterator tmp = token;
		tmp++;
		if ( tmp->type() != Token::Type::IDENTIFER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		token++;
	}

	return result;
}

/*
 * executes the given tokens in a separate scope
 */
ControlFlow::E Interpreter::interpret(const TokenList& tokens, Object* result)
{
	// reset control flow to normal
	mControlFlow = ControlFlow::Normal;

	pushScope();
		pushTokens(tokens);
			TokenIterator start = getTokens().begin();
			TokenIterator end = getTokens().end();

			process(result, start, end);
		popTokens();

		// let the garbage collector do it's magic after we gathered our result
		garbageCollector();
	popScope();

	return mControlFlow;
}

void Interpreter::parseCondition(Object *result, TokenIterator& start)
{
	parseExpression(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::COMPARE_EQUAL &&
			 op != Token::Type::COMPARE_GREATER &&
			 op != Token::Type::COMPARE_GREATER_EQUAL &&
			 op != Token::Type::COMPARE_LESS &&
			 op != Token::Type::COMPARE_LESS_EQUAL &&
			 op != Token::Type::COMPARE_UNEQUAL ) {
			 break;
		}

		start++;	// consume comparator token

		Object v2;
		parseExpression(&v2, start);

		switch ( op ) {
			case Token::Type::COMPARE_EQUAL:
				*result = BoolObject(operator_binary_equal(result, &v2));
				break;
			case Token::Type::COMPARE_GREATER:
				*result = BoolObject(operator_binary_greater(result, &v2));
				break;
			case Token::Type::COMPARE_GREATER_EQUAL:
				*result = BoolObject(operator_binary_greater_equal(result, &v2));
				break;
			case Token::Type::COMPARE_LESS:
				*result = BoolObject(operator_binary_less(result, &v2));
				break;
			case Token::Type::COMPARE_LESS_EQUAL:
				*result = BoolObject(operator_binary_less_equal(result, &v2));
				break;
			case Token::Type::COMPARE_UNEQUAL:
				*result = BoolObject(!operator_binary_equal(result, &v2));
				break;
			default:
				break;
		}
	}
}

void Interpreter::parseExpression(Object *result, TokenIterator& start)
{
	parseFactors(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::BITAND &&
			 op != Token::Type::BITCOMPLEMENT &&
			 op != Token::Type::BITOR &&
			 op != Token::Type::MATH_ADDITION &&
			 op != Token::Type::MATH_SUBTRACT ) {
			return;
		}

		start++;	// consume operator token

		Object v2;
		parseFactors(&v2, start);

		switch ( op ) {
			case Token::Type::BITAND:
				operator_binary_bitand(result, &v2);
				break;
			case Token::Type::BITCOMPLEMENT:
				operator_binary_bitcomplement(result, &v2);
				break;
			case Token::Type::BITOR:
				operator_binary_bitor(result, &v2);
				break;
			case Token::Type::MATH_ADDITION:
				operator_binary_plus(result, &v2);
				break;
			case Token::Type::MATH_SUBTRACT:
				operator_binary_subtract(result, &v2);
				break;
			default:
				break;
		}
	}
}

void Interpreter::parseFactors(Object *result, TokenIterator& start)
{
	parseInfixPostfix(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIVIDE &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTIPLY ) {
			return;
		}

		start++;	// consume operator token

		Object v2;
		parseInfixPostfix(&v2, start);

		switch ( op ) {
			case Token::Type::MATH_DIVIDE:
				operator_binary_divide(result, &v2);
				break;
			case Token::Type::MATH_MODULO:
				operator_binary_modulo(result, &v2);
				break;
			case Token::Type::MATH_MULTIPLY:
				operator_binary_multiply(result, &v2);
				break;
			default:
				break;
		}
	}
}

void Interpreter::parseInfixPostfix(Object *result, TokenIterator& start)
{
	Token::Type::E op = start->type();

	// infix
	switch ( op ) {
		case Token::Type::MATH_SUBTRACT: {
			start++;

			Object tmp;
			parseExpression(&tmp, start);

			operator_unary_minus(&tmp);

			operator_binary_assign(result, &tmp);
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			start++;
			parseExpression(result, start);
			operator_unary_decrement(result);
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			start++;
			parseExpression(result, start);
			operator_unary_increment(result);
		} break;
		case Token::Type::OPERATOR_NOT: {
			start++;
			expression(result, start);
			operator_unary_not(result);
		} break;
		case Token::Type::PARENTHESIS_OPEN: {
			start++;	// consume operator token

			expression(result, start);

			expect(Token::Type::PARENTHESIS_CLOSE, start);

			start++;	// consume operator token
		} break;
		default: {
			parseTerm(result, start);
		} break;
	}

	op = start->type();

	// postfix
	switch ( op ) {
/*
		case Token::Type::BRACKET_OPEN: {
			start++;	// consume operator token

			Object tmp;
			expression(&tmp, start);

			expect(Token::Type::BRACKET_CLOSE, start);

			operator_trinary_array(result, &tmp, result);

			start++;	// consume operator token
		} break;
*/
		case Token::Type::OPERATOR_DECREMENT: {
			operator_unary_decrement(result);
			start++;
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			operator_unary_increment(result);
			start++;
		} break;
		case Token::Type::OPERATOR_IS: {
			start++;

			Symbol* symbol = identify(start);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("unkown identifier '" + start->content() + "' found", start->position());
			}

			*result = BoolObject(operator_binary_is(result, symbol));

			start++;
		} break;
		case Token::Type::OPERATOR_NOT: {
			operator_unary_validate(result);
			start++;
		} break;
		default: {
		} break;
	}
}

void Interpreter::parseTerm(Object *result, TokenIterator& start)
{
	switch ( start->type() ) {
		case Token::Type::CONST_BOOLEAN: {
			BoolObject tmp(Tools::stringToBool(start->content()));
			operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_DOUBLE: {
			DoubleObject tmp(Tools::stringToDouble(start->content()));
			operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_FLOAT: {
			FloatObject tmp(Tools::stringToFloat(start->content()));
			operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_INTEGER: {
			IntegerObject tmp(Tools::stringToInt(start->content()));
			operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_LITERAL: {
			StringObject tmp(start->content());
			operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_NUMBER: {
			NumberObject tmp(Tools::stringToNumber(start->content()));
			operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::IDENTIFER:
		case Token::Type::TYPE: {
			// find out if we have to execute a method or simply get a stored variable

			TokenIterator tmpToken = start;
			Symbol *symbol = identify(start);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}

			switch ( symbol->getSymbolType() ) {
				case Symbol::IType::MethodSymbol:
					process_method(tmpToken, result);
					start = tmpToken;
					start++;
					break;
				case Symbol::IType::ObjectSymbol:
					operator_binary_assign(result, static_cast<Object*>(symbol));
					start++;
					break;
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::BluePrintObjectSymbol: {
					std::string newType = static_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename();
					start++;

					Object tmp;
					expression(&tmp, start);

					typecast(&tmp, newType);

					operator_binary_assign(result, &tmp);
				} break;
				case Symbol::IType::NamespaceSymbol:
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol resolved", start->position());
			}
		} break;
		case Token::Type::KEYWORD: {
			TokenIterator semicolon = findNext(start, Token::Type::SEMICOLON);

			process(result, start, semicolon, Token::Type::SEMICOLON);
		} break;
		case Token::Type::SEMICOLON: {
		} break;
		default: {
			throw Common::Exceptions::SyntaxError("identifier, literal or number expected but " + start->content() + " found", start->position());
		} break;
	}
}

void Interpreter::popScope()
{
	if ( mScopeStack.empty() ) {
		throw Common::Exceptions::Exception("tried to pop beyond stack!");
	}

	SymbolScope* scope = mScopeStack.back();

	mScopeStack.pop_back();

	delete scope;
}

void Interpreter::popTokens()
{
	mTokenStack.pop_back();
}

/*
 * loop through all tokens and redirect to the corresponding method
 */
void Interpreter::process(Object *result, TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	while ( ( (token != getTokens().end()) && (token != end) ) &&
			( (token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE) ) ) {

		if ( mControlFlow != ControlFlow::Normal ) {
			break;		// control flow has been broken, time to stop processing
		}

		Core::Debugger::GetInstance().notify(getScope(), (*token));		// notify debugger

		switch ( token->type() ) {
			case Token::Type::IDENTIFER:
			case Token::Type::PROTOTYPE:
			case Token::Type::TYPE:
				process_identifier(token, result, terminator == Token::Type::NIL ? Token::Type::SEMICOLON : terminator);
				break;
			case Token::Type::KEYWORD:
				process_keyword(token, result);
				break;
			case Token::Type::BRACKET_CURLY_OPEN:
				process_scope(token, result);	// this opens a new scope
				break;
			case Token::Type::SEMICOLON:
				break;
			default:
				throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		token++;	// consume token
	}
}

/*
 * syntax:
 * assert( <expression> );
 */
void Interpreter::process_assert(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

    Object condition;
	try {
		expression(&condition, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	if ( !isTrue(condition) ) {
		throw Runtime::Exceptions::AssertionFailed(condition.ToString(), token->position());
	}

	expect(Token::Type::PARENTHESIS_CLOSE, token++);
}

/*
 * syntax:
 * break;
 */
void Interpreter::process_break(TokenIterator& /*token*/)
{
	mControlFlow = ControlFlow::Break;
}

/*
 * syntax:
 * continue;
 */
void Interpreter::process_continue(TokenIterator& /*token*/)
{
	mControlFlow = ControlFlow::Continue;
}

/*
 * syntax:
 * copy <identifier>;
 */
void Interpreter::process_copy(TokenIterator& token, Object* result)
{
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + token->content() + "'");
	}
	if ( symbol->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Common::Exceptions::Exception("object symbol expected!");
	}

	if ( symbol == result ) {
		throw Common::Exceptions::Exception("cannot assign copy to same object");
	}

	Runtime::Object* source = static_cast<Runtime::Object*>(symbol);

	if ( source->QualifiedTypename() != result->QualifiedTypename() ) {
		throw Common::Exceptions::Exception("object copies are only allowed to same types");
	}

	result->copy(*source);
}

/*
 * syntax:
 * delete <identifier>;
 */
void Interpreter::process_delete(TokenIterator& token)
{
	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer(token->content(), token->position());
	}

	switch ( symbol->getSymbolType() ) {
		case Symbol::IType::ObjectSymbol: {
			Object *object = static_cast<Object*>(symbol);
			assert(object);

			mControlFlow = object->Destructor();

			*object = Object(object->getName(), object->Filename(), object->Typename(), VALUE_NONE);
		} break;
		case Symbol::IType::BluePrintEnumSymbol:
		case Symbol::IType::BluePrintObjectSymbol:
		case Symbol::IType::MethodSymbol:
		case Symbol::IType::NamespaceSymbol:
		case Symbol::IType::UnknownSymbol:
			throw Common::Exceptions::TypeMismatch("member or local variable expected but symbol '" + symbol->getName() + "' found", token->position());
	}

	token = end;
}

/*
 * syntax:
 * exit;
 */
void Interpreter::process_exit(TokenIterator& /*token*/)
{
	throw ControlFlow::ExitProgram;
}

/*
 * syntax:
 * for ( <expression>; <condition>; <expression> ) { ... }
 */
void Interpreter::process_for(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	TokenIterator initializationBegin = token;

	const TokenIterator conditionBegin = ++findNext(initializationBegin, Token::Type::SEMICOLON);

	const TokenIterator increaseBegin = ++findNext(conditionBegin, Token::Type::SEMICOLON);

	// find next open curly bracket '{'
	TokenIterator expressionEnd = findNext(increaseBegin, Token::Type::PARENTHESIS_CLOSE);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++expressionEnd);

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyBegin = expressionEnd;
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	// process our declaration part
	// {
	Object declarationTmp;
	process(&declarationTmp, initializationBegin, conditionBegin, Token::Type::SEMICOLON);
	// }

	bodyBegin++;		// don't collect scope token
	token = bodyEnd;

	TokenList loopTokens;
	while ( bodyBegin != bodyEnd ) {
		loopTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		// Condition parsing
		// {
		TokenIterator condBegin = conditionBegin;

		if ( std::distance(condBegin, increaseBegin) > 1 ) {
			Object condition;
			try {
				expression(&condition, condBegin);
			}
			catch ( ControlFlow::E &e ) {
				mControlFlow = e;
				return;
			}

			if ( !isTrue(condition) ) {
				break;
			}
		}
		// }

		// Body parsing
		// {
		ControlFlow::E controlflow = interpret(loopTokens, result);

		switch ( controlflow ) {
			case ControlFlow::Break: mControlFlow = ControlFlow::Normal; return;
			case ControlFlow::Continue: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::ExitProgram: mControlFlow = ControlFlow::ExitProgram; return;
			case ControlFlow::Normal: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::Return: mControlFlow = ControlFlow::Return; return;
			case ControlFlow::Throw: mControlFlow = ControlFlow::Throw; return;
		}
		// }

		// Expression parsing
		// {
		TokenIterator exprBegin = increaseBegin;

		Object expressionTmp;
		process(&expressionTmp, exprBegin, expressionEnd, Token::Type::PARENTHESIS_CLOSE);
		// }
	}
}

/*
 * executes a method, processes an assign statement and instanciates new types
 */
void Interpreter::process_identifier(TokenIterator& token, Object* /*result*/, Token::Type::E terminator)
{
	TokenIterator tmpToken = token;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + token->content() + "' not found", token->position());
	}

	if ( symbol->getSymbolType() == Symbol::IType::BluePrintEnumSymbol || symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
		process_type(token, symbol);
	}
	else if ( symbol->getSymbolType() == Symbol::IType::MethodSymbol ) {
		token = tmpToken;	// reset token after call to identify

		try {
			Object tmpObject;
			process_method(token, &tmpObject);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}
	}
	else if ( symbol->getSymbolType() == Symbol::IType::ObjectSymbol ) {
		// try to find an assignment token
		TokenIterator assign = findNext(token, Token::Type::ASSIGN, terminator);
		// find next terminator token
		TokenIterator end = findNext(assign, terminator);

		Object* object = static_cast<Object*>(symbol);
		if ( object->isConst() ) {	// we tried to modify a const symbol (i.e. member, parameter or constant local variable)
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + object->getFullScopeName() + "'", token->position());
		}
		if ( object->isMember() && static_cast<Method*>(mOwner)->isConst() ) {	// we tried to modify a member in a const method
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify member '" + object->getFullScopeName() + "' in const method '" + getScope()->getScopeName() + "'", token->position());
		}

		try {
			expression(object, ++assign);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		if ( !object->isConst() && object->isFinal() ) {
			// we have modified a final symbol for the first time, we now have to set it so const
			object->setConst(true);
			object->setFinal(false);

			object->setMutability(Mutability::Const);
		}

		// assign == end should now be true
		token = end;
	}
	else {
		throw Common::Exceptions::Exception("invalid symbol type found!");
	}
}

/*
 * syntax:
 * if ( <expression> ) { ... }
 * else { ... }
 */
void Interpreter::process_if(TokenIterator& token, Object *result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;		// don't collect scope token
	token = bodyEnd;	// no matter what, at least set our token to our if-block's end

	// collect all tokens for our if-block
	TokenList ifTokens;
	while ( bodyBegin != bodyEnd ) {
		ifTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	if ( bodyEnd != getTokens().end() ) {
		bodyEnd++;
	}

	bool targetReached = true;	// initially don't collect else-block tokens
	TokenIterator elseBegin = getTokens().end();
	TokenIterator elseEnd = getTokens().end();

	// look for an else-token
	if ( bodyEnd != getTokens().end() && (bodyEnd->type() == Token::Type::KEYWORD && bodyEnd->content() == "else") ) {
		elseBegin = findNext(bodyEnd, Token::Type::BRACKET_CURLY_OPEN);
		// find next balanced '{' & '}' pair
		elseEnd = findNextBalancedCurlyBracket(elseBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		for ( ; ; ) {
			// check if there is another if after our else-block
			TokenIterator tmpIf = elseEnd;
			tmpIf++;
			if ( tmpIf != getTokens().end() && tmpIf->type() == Token::Type::KEYWORD && tmpIf->content() == "else" ) {
				// find next balanced '{' & '}' pair
				elseEnd = findNextBalancedCurlyBracket(tmpIf, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

				continue;
			}

			token = elseEnd;
			break;
		}

		// reset elseBegin to bodyEnd + 1
		elseBegin = ++bodyEnd;

		targetReached = false;
	}

	TokenList elseTokens;

	while ( !targetReached ) {
		if ( elseBegin == elseEnd ) {
			targetReached = true;
		}

		elseTokens.push_back((*elseBegin));
		elseBegin++;
	}


    Object condition;
	try {
		expression(&condition, condBegin);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	if ( isTrue(condition) ) {
		mControlFlow = interpret(ifTokens, result);
	}
	else if ( !elseTokens.empty() ) {
		mControlFlow = interpret(elseTokens, result);
	}
}

void Interpreter::process_keyword(TokenIterator& token, Object *result)
{
	std::string keyword = (*token++).content();

	if ( keyword == KEYWORD_ASSERT ) {
		process_assert(token);
	}
	else if ( keyword == KEYWORD_BREAK ) {
		process_break(token);
	}
	else if ( keyword == KEYWORD_CONTINUE ) {
		process_continue(token);
	}
	else if ( keyword == KEYWORD_COPY ) {
		process_copy(token, result);
	}
	else if ( keyword == KEYWORD_DELETE ) {
		process_delete(token);
	}
	else if ( keyword == KEYWORD_EXIT ) {
		process_exit(token);
	}
	else if ( keyword == KEYWORD_FOR ) {
		process_for(token, result);
	}
	else if ( keyword == KEYWORD_IF ) {
		process_if(token, result);
	}
	else if ( keyword == KEYWORD_NEW ) {
		process_new(token, result);
	}
	else if ( keyword == KEYWORD_PRINT ) {
		process_print(token);
	}
	else if ( keyword == KEYWORD_RETURN ) {
		process_return(token, result);
	}
	else if ( keyword == KEYWORD_SWITCH ) {
		process_switch(token, result);
	}
	else if ( keyword == KEYWORD_THROW ) {
		process_throw(token, result);
	}
	else if ( keyword == KEYWORD_TRY ) {
		process_try(token, result);
	}
	else if ( keyword == KEYWORD_WHILE ) {
		process_while(token, result);
	}
}

/*
 * syntax:
 * <type> <identifier>(<parameter list>);
 */
void Interpreter::process_method(TokenIterator& token, Object *result)
{
	TokenIterator tmp = token;

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	std::list<Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		objectList.push_back(Object());

		Object *obj = &objectList.back();
		try {
			expression(obj, tmp);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		params.push_back(
			Parameter(obj->getName(), obj->QualifiedOutterface(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj)
		);

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COMMA);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	Method* method = static_cast<Method*>(identifyMethod(token, params));

	if ( !method) {
		throw Common::Exceptions::UnknownIdentifer("could not resolve identifier '" + token->content() + "' with parameters '" + toString(params) + "'", token->position());
	}

	// compare callee's constness with its parent's constness
	Object* calleeParent = dynamic_cast<Object*>(method->getEnclosingScope());
	if ( calleeParent && calleeParent->isConst() && !method->isConst() ) {
		// we want to call a non-const method of a const object... neeeeey!
		throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed for const object '" + calleeParent->getFullScopeName() + "'", token->position());
	}

	// check caller's constness
	if ( static_cast<Method*>(mOwner)->isConst() ) {
		if ( mOwner->getEnclosingScope() == method->getEnclosingScope() && !method->isConst() ) {
			// check target method's constness
			// this is a const method and we want to call a non-const method... neeeeey!
			throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + getScope()->getFullScopeName() + "'", token->position());
		}
	}

	ControlFlow::E controlflow = method->execute(params, result, (*token));

	switch ( controlflow ) {
		case ControlFlow::ExitProgram:
			mControlFlow = ControlFlow::ExitProgram;
			break;
		case ControlFlow::Throw:
			mControlFlow = ControlFlow::Throw;
			mExceptionData = method->getExceptionData();
			throw ControlFlow::Throw;			// throw even further
		default:
			break;
	}

	token = closed;
}

/*
 * syntax:
 * new <Typename>([<parameter list>]);
 */
void Interpreter::process_new(TokenIterator& token, Object *result)
{
	std::string name;
	std::string type = token->content();

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + type + "'");
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::Exception("blueprint symbol expected!");
	}

	expect(Token::Type::PARENTHESIS_OPEN, ++token);

	TokenIterator opened = token;
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	token = closed;

	std::list<Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	TokenIterator tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		objectList.push_back(Object());

		Object *obj = &objectList.back();
		try {
			expression(obj, tmp);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		params.push_back(
			//Parameter(obj->getName(), obj->QualifiedTypename(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj)
			Parameter(obj->getName(), obj->Outterface(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj)
		);

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COMMA);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	// create initialized instance of new object
	*result = *getRepository()->createInstance(static_cast<Designtime::BluePrintObject*>(symbol), name, true);

	// execute new object's constructor
	mControlFlow = result->Constructor(params);
}

/*
 * syntax:
 * print(<expression>);
 */
void Interpreter::process_print(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	Object text;
	try {
		expression(&text, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	::Utils::PrinterDriver::getInstance()->print(text.getValue().toStdString(), token->position().mFile, token->position().mLine);

	expect(Token::Type::PARENTHESIS_CLOSE, token++);
}

/*
 * syntax:
 * return [<expression>];
 */
void Interpreter::process_return(TokenIterator& token, Object *result)
{
	try {
		expression(result, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	mControlFlow = ControlFlow::Return;
}

// syntax:
// { <statement> }
void Interpreter::process_scope(TokenIterator& token, Object* result)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token++);

	TokenIterator scopeBegin = token;
	TokenIterator scopeEnd = findNextBalancedCurlyBracket(scopeBegin, getTokens().end());

	token = scopeEnd;

	TokenList scopeTokens;
	while ( scopeBegin != scopeEnd ) {
		scopeTokens.push_back((*scopeBegin));
		scopeBegin++;
	}

	mControlFlow = interpret(scopeTokens, result);

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
}

/*
 * syntax:
 * switch ( <expression> ) {
 *		[ case <identifier>: { ... } ]
 *		[ default: { ... } ]
 * }
 */
void Interpreter::process_switch(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	// evaluate switch-expression
	Object expr;
	try {
		expression(&expr, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;	// don't collect scope token
	token = bodyEnd;

	class CaseBlock
	{
	public:
		CaseBlock(TokenIterator begin, TokenIterator end)
		: mBegin(begin),
		  mEnd(end)
		{ }

		TokenIterator mBegin;
		TokenIterator mEnd;
	};
	typedef std::list<CaseBlock> CaseBlocks;

	CaseBlocks caseBlocks;
	CaseBlock defaultBlock = CaseBlock(getTokens().end(), getTokens().end());

	while ( bodyBegin != bodyEnd ) {
		if ( bodyBegin->type() == Token::Type::KEYWORD && bodyBegin->content() == KEYWORD_CASE ) {
			TokenIterator tmp = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			caseBlocks.push_back(CaseBlock(bodyBegin, tmp));

			bodyBegin = tmp;
		}
		else if ( bodyBegin->type() == Token::Type::KEYWORD && bodyBegin->content() == KEYWORD_DEFAULT ) {
			if ( defaultBlock.mBegin != getTokens().end() ) {
				throw Common::Exceptions::SyntaxError("duplicate default entry for switch statement");
			}

			TokenIterator tmp = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			defaultBlock = CaseBlock(bodyBegin, tmp);

			bodyBegin = tmp;
		}
		bodyBegin++;
	}

	// loop through all case-labels and match their expressions against the switch-expression
	for ( CaseBlocks::iterator it = caseBlocks.begin(); it != caseBlocks.end(); ++it ) {
		it->mBegin++;

		Object condition;
		try {
			expression(&condition, it->mBegin);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		if ( operator_binary_equal(&expr, &condition) ) {
			expect(Token::Type::COLON, it->mBegin++);
			expect(Token::Type::BRACKET_CURLY_OPEN, it->mBegin++);	// don't collect scope token

			// collect case-block tokens
			TokenList caseTokens;
			while ( it->mBegin != it->mEnd ) {
				caseTokens.push_back((*it->mBegin));
				it->mBegin++;
			}

			mControlFlow = interpret(caseTokens, result);

			switch ( mControlFlow ) {
				case ControlFlow::Break:
					mControlFlow = ControlFlow::Normal;
					return;	// stop matching the remaining case-statements
				case ControlFlow::Continue:
				case ControlFlow::Normal:
					mControlFlow = ControlFlow::Normal;
					break;	// continue matching the remaining case-statements
				case ControlFlow::ExitProgram:
				case ControlFlow::Return:
				case ControlFlow::Throw:
					return;	// no further processing, keep current control flow state
			}
		}
	}

	// execute the default block (if present)
	if ( defaultBlock.mBegin != getTokens().end() ) {
		defaultBlock.mBegin++;
		expect(Token::Type::COLON, defaultBlock.mBegin++);
		expect(Token::Type::BRACKET_CURLY_OPEN, defaultBlock.mBegin++);

		// collect default-block tokens
		TokenList defaultTokens;
		while ( defaultBlock.mBegin != defaultBlock.mEnd ) {
			defaultTokens.push_back((*defaultBlock.mBegin));
			defaultBlock.mBegin++;
		}

		mControlFlow = interpret(defaultTokens, result);

		switch ( mControlFlow ) {
			case ControlFlow::Break:
			case ControlFlow::Continue:
			case ControlFlow::Normal:
				mControlFlow = ControlFlow::Normal;
				break;	// statement has no effect because the default section is the last executed section
			case ControlFlow::ExitProgram:
			case ControlFlow::Return:
			case ControlFlow::Throw:
				return;	// no further processing, keep current control flow state
		}
	}
}

/*
 * syntax:
 * throw [<expression>];
 */
void Interpreter::process_throw(TokenIterator& token, Object* /*result*/)
{
	// TODO: check if our parent scope is a method that is allowed to throw exceptions

	Object* data = getRepository()->createInstance(GENERIC_OBJECT);
	try {
		expression(data, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	mControlFlow = ControlFlow::Throw;
	mExceptionData = ExceptionData(data, token->position());

	expect(Token::Type::SEMICOLON, token);

	// notify our debugger that an exception has been thrown
	Core::Debugger::GetInstance().notifyException(getScope(), (*token));
}

/*
 * syntax:
 * try { ... }
 * [ catch { ... } ]
 * [ finally { ... } ]
 */
void Interpreter::process_try(TokenIterator& token, Object* result)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	// find next open curly bracket '{'
	TokenIterator tryBegin = token;
	// find next balanced '{' & '}' pair
	TokenIterator tryEnd = findNextBalancedCurlyBracket(tryBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	tryBegin++;	// don't collect scope tokens
	token = tryEnd;

	// collect try-block tokens
	TokenList tryTokens;
	while ( tryBegin != tryEnd ) {
		tryTokens.push_back((*tryBegin));
		tryBegin++;
	}

	// process try-block
	mControlFlow = interpret(tryTokens, result);

	TokenIterator tmp = lookahead(token, 1);

	std::list<TokenIterator> catchTokens;
	TokenIterator finallyToken = getTokens().end();

	for ( ; ; ) {
		if ( tmp != getTokens().end() && tmp->content() == KEYWORD_CATCH ) {
			catchTokens.push_back(tmp);

			tmp = findNextBalancedCurlyBracket(tmp, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			token = tmp;	// set exit token
		}
		else if ( tmp != getTokens().end() && tmp->content() == KEYWORD_FINALLY ) {
			if ( finallyToken != getTokens().end() ) {
				throw Common::Exceptions::SyntaxError("multiple finally blocks are not allowed");
			}

			finallyToken = tmp;
			tmp = findNextBalancedCurlyBracket(tmp, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			token = tmp;	// set exit token
		}
		else {
			break;	// reached end of try-catch-finally-block
		}

		tmp++;
	}

	if ( mControlFlow == ControlFlow::Throw ) {
		mControlFlow = ControlFlow::Normal;

		for ( std::list<TokenIterator>::const_iterator it = catchTokens.begin(); it != catchTokens.end(); ++it ) {
			TokenIterator catchIt = (*it);
			catchIt++;

			// parse exception type (if present)
			if ( catchIt->type() == Token::Type::PARENTHESIS_OPEN ) {
				catchIt++;

				Symbol* symbol = identify(catchIt);
				if ( !symbol ) {
					throw Common::Exceptions::UnknownIdentifer("identifier '" + token->content() + "' not found", catchIt->position());
				}
				if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol && symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
					throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", catchIt->position());
				}

				// create new exception type instance
				Object* type = process_type(catchIt, symbol);

				expect(Token::Type::PARENTHESIS_CLOSE, catchIt++);

				if ( !type || !mExceptionData.getData() ) {
					throw Common::Exceptions::Exception("could not create exception type instance", catchIt->position());
				}

				if ( type->QualifiedTypename() != mExceptionData.getData()->QualifiedTypename() &&
					 type->Typename() != mExceptionData.getData()->Typename() ) {
					// get rid of our newly created exception type instance
					getScope()->undefine(type->getName(), type);
					mRepository->removeReference(type);
					continue;
				}

				operator_binary_assign(type, mExceptionData.getData());
			}

			expect(Token::Type::BRACKET_CURLY_OPEN, catchIt);

			// find next open curly bracket '{'
			TokenIterator catchBegin = catchIt;
			// find next balanced '{' & '}' pair
			TokenIterator catchEnd = findNextBalancedCurlyBracket(catchBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			catchBegin++;		// don't collect scope token
			token = catchEnd;

			// collect catch-block tokens
			TokenList tokens;
			while ( catchBegin != catchEnd ) {
				tokens.push_back((*catchBegin));
				catchBegin++;
			}

			// execute catch-block if an exception has been thrown
			mControlFlow = interpret(tokens, result);
			break;
		}
	}

	if ( finallyToken != getTokens().end() ) {
		finallyToken++;
		expect(Token::Type::BRACKET_CURLY_OPEN, finallyToken);

		// find next open curly bracket '{'
		TokenIterator finallyBegin = finallyToken;
		// find next balanced '{' & '}' pair
		TokenIterator finallyEnd = findNextBalancedCurlyBracket(finallyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		finallyBegin++;		// don't collect scope token;
		token = finallyEnd;

		// collect finally-block tokens
		TokenList finallyTokens;
		while ( finallyBegin != finallyEnd ) {
			finallyTokens.push_back((*finallyBegin));
			finallyBegin++;
		}

		// TODO: should we execute the finally-block in any case (i.e. even though a return has been issued by the user)?
		if ( mControlFlow == ControlFlow::Normal ) {
			mControlFlow = interpret(finallyTokens, result);
		}
	}
}

/*
 * syntax:
 * <type> <identifier> [= <initialization>]
 */
Object* Interpreter::process_type(TokenIterator& token, Symbol* symbol)
{
	bool isArray = false;
	bool isConst = false;
	bool isFinal = false;
	std::string name;
	int size = 0;

	token++;
	name = token->content();

	expect(Token::Type::IDENTIFER, token);

	token++;

	if (  token->type() == Token::Type::BRACKET_OPEN ) {
		isArray = true;
		token++;

		Object tmp;
		try {
			expression(&tmp, token);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return 0;
		}

		size = tmp.getValue().toInt();

		expect(Token::Type::BRACKET_CLOSE, token++);
	}

	std::string tmpStr = token->content();
	if ( tmpStr == MODIFIER_CONST || tmpStr == MODIFIER_FINAL ) {
		token++;

		if ( tmpStr == MODIFIER_CONST ) { isConst = true; }
		else if ( tmpStr == MODIFIER_FINAL ) { isFinal = true; }
	}

	TokenIterator assign = getTokens().end();
	if ( token->type() == Token::Type::ASSIGN ) {
		assign = ++token;
	}

	Object *object = dynamic_cast<Object*>(getScope()->resolve(name, true));
	if ( object ) {
		throw Common::Exceptions::DuplicateIdentifier("duplicate identifier '" + name + "' created", token->position());
	}

	object = getRepository()->createInstance(static_cast<Designtime::BluePrintObject*>(symbol), name, false);

	getScope()->define(name, object);

	if ( isArray ) object->setArray(true, (size_t)size);
	if ( isConst ) object->setConst(true);
	if ( isFinal ) object->setFinal(true);

	if ( assign != getTokens().end() ) {
		// execute assignment statement
		try {
			Object tmp;
			expression(&tmp, token);

			operator_binary_assign(object, &tmp);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return 0;
		}
	}

	// this has been removed to allow type declarations without a trailing semicolon (like in "catch ( Exception e )" )
	//expect(Token::Type::SEMICOLON, token);	// make sure everything went exactly the way we wanted

	return object;
}

/*
 * syntax:
 * while ( <condition> ) { ... }
 */
void Interpreter::process_while(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;	// don't collect scope token;
	token = bodyEnd;

	TokenList statementTokens;
	while ( bodyBegin != bodyEnd ) {
		statementTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		TokenIterator tmp = condBegin;

		Object condition;
		try {
			expression(&condition, tmp);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		if ( !isTrue(condition) ) {
			break;
		}

		ControlFlow::E controlflow = interpret(statementTokens, result);

		switch ( controlflow ) {
			case ControlFlow::Break: mControlFlow = ControlFlow::Normal; return;
			case ControlFlow::Continue: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::ExitProgram: mControlFlow = ControlFlow::ExitProgram; return;
			case ControlFlow::Normal: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::Return: mControlFlow = ControlFlow::Return; return;
			case ControlFlow::Throw: mControlFlow = ControlFlow::Throw; return;
		}
	}
}

void Interpreter::pushScope()
{
	SymbolScope* scope = new SymbolScope("", getScope());

	mScopeStack.push_back(scope);
}

void Interpreter::pushTokens(const TokenList& tokens)
{
	mTokenStack.push_back(tokens);
}

void Interpreter::setRepository(Repository *repository)
{
	mRepository = repository;
}

void Interpreter::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}


}
}
