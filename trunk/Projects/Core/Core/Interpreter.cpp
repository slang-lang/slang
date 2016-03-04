
// Header
#include "Interpreter.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Printer.h>
#include "Object.h"
#include "OperatorOverloading.h"
#include "Repository.h"
#include "System.h"
#include "Tools.h"
#include "TypeCast.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Interpreter::Interpreter(IScope *scope, const std::string& name)
: LocalScope(name, scope),
  mControlFlow(ControlFlow::Normal),
  mRepository(0)
{
}

Interpreter::~Interpreter()
{
	garbageCollector();
}

ControlFlow::E Interpreter::execute(Object *result)
{
	pushTokens(mTokens);
		TokenIterator start = getTokens().begin();
		TokenIterator end = getTokens().end();

		process(result, start, end);
	popTokens();

	// let the garbage collector do it's magic after we gathered our result
	garbageCollector();

	return mControlFlow;
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

		// consume operator token
		start++;

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
	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->first != KEYWORD_BASE && it->first != KEYWORD_THIS &&
			 it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
			mRepository->removeReference(static_cast<Object*>(it->second));
		}

		undefine(it->first, it->second);
	}
	mSymbols.clear();
}

const TokenList& Interpreter::getTokens() const
{
	return mTokenStack.back();
}

ControlFlow::E Interpreter::interpret(const TokenList& tokens, Object* result)
{
	// this creates a new scope

	Interpreter interpreter(this, getScopeName());
	interpreter.setConst(isConst());
	interpreter.setFinal(isFinal());
	interpreter.setLanguageFeatureState(getLanguageFeatureState());
	interpreter.setRepository(mRepository);
	interpreter.setTokens(tokens);

	ControlFlow::E controlflow = interpreter.execute(result);

	return controlflow;
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

		start++;	// consume comperator token

		Object v2;
		parseExpression(&v2, start);

		switch ( op ) {
			case Token::Type::COMPARE_EQUAL:
				*result = BoolObject(operator_equal(result, &v2));
				break;
			case Token::Type::COMPARE_GREATER:
				*result = BoolObject(operator_greater(result, &v2));
				break;
			case Token::Type::COMPARE_GREATER_EQUAL:
				*result = BoolObject(operator_greater_equal(result, &v2));
				break;
			case Token::Type::COMPARE_LESS:
				*result = BoolObject(operator_less(result, &v2));
				break;
			case Token::Type::COMPARE_LESS_EQUAL:
				*result = BoolObject(operator_less_equal(result, &v2));
				break;
			case Token::Type::COMPARE_UNEQUAL:
				*result = BoolObject(!operator_equal(result, &v2));
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
				operator_bitand(result, &v2);
				break;
			case Token::Type::BITCOMPLEMENT:
				operator_bitcomplement(result, &v2);
				break;
			case Token::Type::BITOR:
				operator_bitor(result, &v2);
				break;
			case Token::Type::MATH_ADDITION:
				operator_plus(result, &v2);
				break;
			case Token::Type::MATH_SUBTRACT:
				operator_subtract(result, &v2);
				break;
			default:
				break;
		}
	}
}

void Interpreter::parseFactors(Object *result, TokenIterator& start)
{
	if ( start->type() == Token::Type::PARENTHESIS_OPEN) {
		start++;	// consume operator token

		expression(result, start);

		expect(Token::Type::PARENTHESIS_CLOSE, start);

		start++;	// consume operator token
	}
	else {
		parseInfixPostfix(result, start);
	}

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIVIDE &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTIPLY ) {
			return;
		}

		start++;	// consume operator token

		Object v2;
		if ( start->type() == Token::Type::PARENTHESIS_OPEN) {
			start++;	// consume operator token
			expression(&v2, start);

			expect(Token::Type::PARENTHESIS_CLOSE, start);

			start++;	// consume operator token
		}
		else {
			parseInfixPostfix(&v2, start);
		}

		switch ( op ) {
			case Token::Type::MATH_DIVIDE:
				operator_divide(result, &v2);
				break;
			case Token::Type::MATH_MODULO:
				operator_modulo(result, &v2);
				break;
			case Token::Type::MATH_MULTIPLY:
				operator_multiply(result, &v2);
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
		case Token::Type::NOT: {
			start++;
			parseTerm(result, start);
			operator_unary_not(result);
		} break;
		case Token::Type::MATH_SUBTRACT: {
			start++;
			parseTerm(result, start);
			operator_unary_minus(result);
		} break;
		case Token::Type::TYPE: {
			std::string newType = start->content();
			start++;
			parseTerm(result, start);
			typecast(result, newType);
		} break;
		default: {
			parseTerm(result, start);
		} break;
	}

	op = start->type();

	// postfix
	switch ( op ) {
		case Token::Type::DECREMENT: {
			operator_unary_decrement(result);
			start++;
		} break;
		case Token::Type::INCREMENT: {
			operator_unary_increment(result);
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
			operator_assign(result, &tmp);
		} break;
		case Token::Type::CONST_FLOAT: {
			FloatObject tmp(Tools::stringToFloat(start->content()));
			operator_assign(result, &tmp);
		} break;
		case Token::Type::CONST_INTEGER: {
			IntegerObject tmp(Tools::stringToInt(start->content()));
			operator_assign(result, &tmp);
		} break;
		case Token::Type::CONST_LITERAL: {
			StringObject tmp(start->content());
			operator_assign(result, &tmp);
		} break;
		case Token::Type::CONST_NUMBER: {
			NumberObject tmp(Tools::stringToFloat(start->content()));
			operator_assign(result, &tmp);
		} break;
		case Token::Type::IDENTIFER: {
			// find out if we have to execute a method
			// or simply get a stored variable

			Symbol *symbol = resolve(start->content());
			if ( !symbol ) {
				throw Utils::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}

			switch ( symbol->getType() ) {
				case Symbol::IType::MethodSymbol:
					process_method(start, result);
					break;
				case Symbol::IType::AtomicTypeSymbol:
				case Symbol::IType::ObjectSymbol:
					*result = *static_cast<Object*>(symbol);
					break;
				case Symbol::IType::BluePrintSymbol:
				case Symbol::IType::NamespaceSymbol:
				case Symbol::IType::UnknownSymbol:
					throw Utils::Exceptions::SyntaxError("unexpected symbol resolved", start->position());
					break;
			}
		} break;
		case Token::Type::KEYWORD: {
			process(result, start, getTokens().end(), Token::Type::SEMICOLON);
		} break;
		case Token::Type::SEMICOLON: {
			if ( result->Typename() == VoidObject::TYPENAME ) {
				// this is okay, as long as we have a been called by a return command in a void method
				return;
			}
		} break;
		default: {
			throw Utils::Exceptions::SyntaxError("identifier, literal or number expected but " + start->content() + " found", start->position());
		} break;
	}

	start++;
}

void Interpreter::popTokens()
{
	mTokenStack.pop_back();
}

void Interpreter::process(Object *result, TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	// loop through all keywords and redirect to the corresponding method
	while ( ((token != getTokens().end()) && (token != end) ) &&
			((token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE)) ) {

		if ( mControlFlow != ControlFlow::Normal ) {
			// a return command has been triggered, time to stop processing
			break;
		}

		// decide what we want to do according to the type of token we have
		switch ( token->type() ) {
			case Token::Type::CONST_BOOLEAN:
			case Token::Type::CONST_FLOAT:
			case Token::Type::CONST_INTEGER:
			case Token::Type::CONST_LITERAL:
			case Token::Type::CONST_NUMBER:
				expression(result, token);
				break;
			case Token::Type::IDENTIFER:
				process_identifier(token, result, terminator == Token::Type::NIL ? Token::Type::SEMICOLON : terminator);
				break;
			case Token::Type::KEYWORD:
				process_keyword(token, result);
				break;
			case Token::Type::PROTOTYPE:
			case Token::Type::TYPE:
				process_type(token);
				break;
			case Token::Type::BRACKET_CURLY_OPEN: {
				// this opens a new scope
				process_scope(token, result);
			} break;
			default:
				throw Utils::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
				break;
		}

		token++;	// consume token
	}
}

// syntax:
// assert [(] <expression> [)];
void Interpreter::process_assert(TokenIterator& token)
{
	//expect(Token::Type::PARENTHESIS_OPEN, token);

	// find next open parenthesis
	TokenIterator condBegin = findNext(token, Token::Type::PARENTHESIS_OPEN, Token::Type::SEMICOLON);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(++condBegin, 0, Token::Type::SEMICOLON);
	// find semicolon
	TokenIterator tmp = findNext(condEnd, Token::Type::SEMICOLON);

    Object condition;
	expression(&condition, token);

	System::Assert(condition, token->position());

	token = tmp;
}

// syntax:
// break;
void Interpreter::process_break(TokenIterator& /*token*/)
{
	mControlFlow = ControlFlow::Break;
}

// syntax:
// continue;
void Interpreter::process_continue(TokenIterator& /*token*/)
{
	mControlFlow = ControlFlow::Continue;
}

// syntax:
// delete <identifier>;
void Interpreter::process_delete(TokenIterator& token)
{
	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Symbol *symbol = resolve(token->content());
	if ( !symbol ) {
		throw Utils::Exceptions::UnknownIdentifer(token->content(), token->position());
	}

	switch ( symbol->getType() ) {
		case Symbol::IType::AtomicTypeSymbol:
		case Symbol::IType::ObjectSymbol: {
			Object *object = static_cast<Object*>(symbol);

			*object = Object(object->getName(), object->Filename(), object->Typename(), VALUE_NONE);
		} break;
		case Symbol::IType::BluePrintSymbol:
		case Symbol::IType::MethodSymbol:
		case Symbol::IType::NamespaceSymbol:
		case Symbol::IType::UnknownSymbol:
			throw Utils::Exceptions::TypeMismatch("member or local variable expected but symbol '" + symbol->getName() + "' found", token->position());
	}

	token = end;
}

// syntax:
// for ( <expression>; <condition>; <expression> ) { }
void Interpreter::process_for(TokenIterator& token, Object *result)
{
	// initialization-begin
	TokenIterator initializationBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// initialization-end

	// condition-begin
	const TokenIterator conditionBegin = ++findNext(initializationBegin, Token::Type::SEMICOLON);
	// condition-end

	// increase-begin
	const TokenIterator increaseBegin = ++findNext(conditionBegin, Token::Type::SEMICOLON);
	// increase-end

	// find next open curly bracket '{'
	TokenIterator expressionEnd = findNext(increaseBegin, Token::Type::PARENTHESIS_CLOSE);


	if ( expressionEnd != getTokens().end() ) {
		expressionEnd++;
	}

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyBegin = findNext(increaseBegin, Token::Type::BRACKET_CURLY_OPEN);
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	// process our declaration part
	Object declaration;
	process(&declaration, initializationBegin, conditionBegin, Token::Type::SEMICOLON);

	token = bodyEnd;
	if ( bodyEnd != getTokens().end() ) {
		bodyEnd++;
	}

	TokenList loopTokens;
	while ( bodyBegin != bodyEnd ) {
		loopTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		// Condition parsing
		// {
		TokenIterator condBegin = conditionBegin;

		Object condition;
		expression(&condition, condBegin);

		if ( !isTrue(condition) ) {
			break;
		}
		// }

		// Body parsing
		// {
		ControlFlow::E controlflow = interpret(loopTokens, result);

		switch ( controlflow ) {
			case ControlFlow::Break: mControlFlow = ControlFlow::Normal; return;
			case ControlFlow::Continue: mControlFlow = ControlFlow::Normal; continue;
			case ControlFlow::Normal: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::Return: mControlFlow = ControlFlow::Return; return;
			case ControlFlow::Throw: mControlFlow = ControlFlow::Throw; return;
		}
		// }

		// Expression parsing
		// {
		TokenIterator exprBegin = increaseBegin;
		TokenList exprTokens;

		while ( exprBegin != expressionEnd ) {
			exprTokens.push_back((*exprBegin));
			exprBegin++;
		}

		pushTokens(exprTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			Object result;
			process(&result, tmpBegin, tmpEnd, Token::Type::PARENTHESIS_CLOSE);
		}
		popTokens();
		// }
	}
}

// executes a method or processes an assign statement
void Interpreter::process_identifier(TokenIterator& token, Object *result, Token::Type::E terminator)
{
(void)result;

	// try to find assignment token
	TokenIterator assign = findNext(token, Token::Type::ASSIGN, terminator);
	// find next semicolon
	TokenIterator end = findNext(assign, terminator);

	std::string identifier = token->content();

    if ( assign == token ) {
        // we don't have an assignment but a method call
		Object tmp;
		expression(&tmp, token);

        token = end;
        return;
    }

	Object *symbol = static_cast<Object*>(resolve(identifier));
	if ( !symbol ) {	// we tried to access an unknown symbol
		throw Utils::Exceptions::UnknownIdentifer("identifier '" + identifier + "' not found", token->position());
	}
	if ( symbol->isConst() ) {	// we tried to modify a const symbol (i.e. member, parameter or constant local variable)
		throw Utils::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + identifier + "'", token->position());
	}
	if ( symbol->isMember() && this->isConst() ) {	// we tried to modify a member in a const method
		throw Utils::Exceptions::ConstCorrectnessViolated("tried to modify member '" + identifier + "' in const method '" + getScopeName() + "'", token->position());
	}

	expression(symbol, ++assign);

	if ( !symbol->isConst() && symbol->isFinal() ) {
		// we have modified a final symbol for the first time, we now have to set it so const
		symbol->setConst(true);
		symbol->setFinal(false);
	}

	// assign == end should now be true
	token = end;
}

// syntax:
// if ( <expression> ) {
// ...
// }
// else {
// ...
// }
void Interpreter::process_if(TokenIterator& token, Object *result)
{
	// find next open parenthesis
	TokenIterator condBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);
	// find next open curly bracket '{'
	TokenIterator bodyBegin = findNext(condEnd, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	// no matter what, at least set our token to our if-block's end
	token = bodyEnd;
	if ( bodyEnd != getTokens().end() ) {
		bodyEnd++;
	}

	// collect all tokens for our if-block
	TokenList ifTokens;
	while ( bodyBegin != bodyEnd ) {
		ifTokens.push_back((*bodyBegin));
		bodyBegin++;
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
	expression(&condition, condBegin);

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
	else if ( keyword == KEYWORD_DELETE ) {
		process_delete(token);
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

// syntax:
// type method(<parameter list>);
void Interpreter::process_method(TokenIterator& token, Object *result)
{
	TokenIterator tmp = token;

	std::string method = token->content();

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	std::list<Object> objectList;
	ParameterList params;

	tmp = opened;
	// loop through all parameters seperated by colons
	while ( tmp != closed ) {
		objectList.push_back(Object());

		Object *obj = &objectList.back();
		expression(obj, tmp);

		params.push_back(
			Parameter(obj->getName(), obj->Typename(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj)
		);

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COLON);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	token = closed;


	std::string member, parent;
	Tools::split(method, parent, member);

	Method *symbol = static_cast<Method*>(resolveMethod(method, params));

	if ( !symbol) {
		throw Utils::Exceptions::UnknownIdentifer("could not resolve method '" + method + "'");
	}

	// check target method's const-ness
	if ( isConst() && !symbol->isConst() ) {	// this is a const method and we want to call a non-const method... neeeeey!
		throw Utils::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + getScopeName() + "'", token->position());
	}

	ControlFlow::E controlflow = static_cast<Method*>(symbol)->execute(params, result);

	if ( controlflow == ControlFlow::Throw ) {
		mControlFlow = ControlFlow::Throw;
	}
}

// syntax:
// new <Object>([<parameter list>]);
void Interpreter::process_new(TokenIterator& token, Object *result)
{
	TokenIterator tmp = token;

	std::string name = ANONYMOUS_OBJECT;
	std::string prototype;

	if ( token->type() == Token::Type::PROTOTYPE ) {
		prototype = token->content();
		token++;
	}

	std::string type = token->content();

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	std::list<Object> objectList;	// this is a hack to prevent the provided object parameters to run out of scope after our while-loop
	ParameterList params;

	tmp = opened;
	// loop through all parameters separated by colons
	while ( tmp != closed ) {
		objectList.push_back(Object());

		Object *obj = &objectList.back();
		expression(obj, tmp);

		params.push_back(
			Parameter(obj->getName(), obj->Typename(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj)
		);

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COLON);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	token = closed;

	*result = *mRepository->createInstance(type, name, prototype);
	result->setRepository(mRepository);
	result->Constructor(params);
}

// syntax:
// print(<expression>);
void Interpreter::process_print(TokenIterator& token)
{
	//expect(Token::Type::PARENTHESIS_OPEN, token);

	// find open parenthesis
	TokenIterator opened = findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find closed parenthesis
	TokenIterator closed = findNextBalancedParenthesis(++opened);
	// find semicolon
	TokenIterator tmp = findNext(closed, Token::Type::SEMICOLON);

	StringObject text;
	expression(&text, opened);

	System::Print(text.getValue(), token->position());

	token = tmp;
}

// syntax:
// return <expression>;
void Interpreter::process_return(TokenIterator& token, Object *result)
{
	expression(result, token);

	mControlFlow = ControlFlow::Return;
}

// syntax:
// { <statement> }
void Interpreter::process_scope(TokenIterator& token, Object* result)
{
	TokenIterator scopeBegin = ++token;
	TokenIterator scopeEnd = findNextBalancedCurlyBracket(scopeBegin, getTokens().end());

	TokenList scopeTokens;
	while ( scopeBegin != scopeEnd ) {
		scopeTokens.push_back((*scopeBegin));
		scopeBegin++;
	}

	mControlFlow = interpret(scopeTokens, result);

	token = scopeEnd;
}

// syntax:
// switch ( <expression> ) {
//		case <identifier>:
//			...
//		break;
// }
void Interpreter::process_switch(TokenIterator& token, Object *result)
{
assert(!"not implemented");
//throw Utils::Exceptions::NotImplemented("switch-case");

	// find next open parenthesis
	TokenIterator expressionBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find next balanced '(' & ')' pair
	TokenIterator expressionEnd = findNextBalancedParenthesis(expressionBegin);
	// find next open curly bracket '{'
	TokenIterator bodyBegin = findNext(expressionEnd, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	token = bodyEnd;
	if ( bodyEnd != getTokens().end() ) {
		bodyEnd++;
	}

	TokenList switchTokens;
	while ( bodyBegin != bodyEnd ) {
		switchTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	TokenIterator tmp = expressionBegin;

	Object value;
	expression(&value, tmp);

	pushTokens(switchTokens);
	{
		TokenIterator tmpBegin = getTokens().begin();
		TokenIterator tmpEnd = getTokens().end();

		process(result, tmpBegin, tmpEnd);
	}
	popTokens();
}

// syntax:
// throw;
void Interpreter::process_throw(TokenIterator& token, Object *result)
{
	TokenIterator begin = token;
	TokenIterator semicolon = findNext(token, Token::Type::SEMICOLON);

	// collect tokens
	TokenList throwTokens;
	while ( begin != semicolon ) {
		throwTokens.push_back((*begin));
		begin++;
	}

	pushTokens(throwTokens);
	{
		TokenIterator tmpBegin = getTokens().begin();
		TokenIterator tmpEnd = getTokens().end();

		process(result, tmpBegin, tmpEnd);
	}
	popTokens();

	mControlFlow = ControlFlow::Throw;

	token = semicolon;
}

// syntax:
// try { } [ catch { } ] [ finally { } ]
void Interpreter::process_try(TokenIterator& token, Object *result)
{
	TokenIterator tmp;

	// find next open curly bracket '{'
	TokenIterator tryBegin = findNext(token, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator tryEnd = findNextBalancedCurlyBracket(tryBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	token = tryEnd;
	if ( tryEnd != getTokens().end() ) {
		tryEnd++;
	}
	tmp = tryEnd;

	// collect try-block tokens
	TokenList tryTokens;
	while ( tryBegin != tryEnd ) {
		tryTokens.push_back((*tryBegin));
		tryBegin++;
	}

	mControlFlow = interpret(tryTokens, result);

	// execute catch-block if an exception has been thrown
	if ( mControlFlow == ControlFlow::Throw ) {
		// reset control flow after try block
		mControlFlow = ControlFlow::Normal;

		if ( tmp != getTokens().end() && tmp->content() == KEYWORD_CATCH ) {
			// find next open curly bracket '{'
			TokenIterator catchBegin = findNext(tmp, Token::Type::BRACKET_CURLY_OPEN);
			// find next balanced '{' & '}' pair
			TokenIterator catchEnd = findNextBalancedCurlyBracket(catchBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			token = catchEnd;
			if ( catchEnd != getTokens().end() ) {
				catchEnd++;
			}
			tmp = catchEnd;

			// collect catch-block tokens
			TokenList catchTokens;
			while ( catchBegin != catchEnd ) {
				catchTokens.push_back((*catchBegin));
				catchBegin++;
			}

			mControlFlow = interpret(catchTokens, result);
		}
	}
	else {
		// reset control flow after try block
		mControlFlow = ControlFlow::Normal;
	}

	// execute finally if present
	if ( tmp != getTokens().end() && tmp->content() == KEYWORD_FINALLY ) {
		// find next open curly bracket '{'
		TokenIterator finallyBegin = findNext(tmp, Token::Type::BRACKET_CURLY_OPEN);
		// find next balanced '{' & '}' pair
		TokenIterator finallyEnd = findNextBalancedCurlyBracket(finallyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		token = finallyEnd;
		if ( finallyEnd != getTokens().end() ) {
			finallyEnd++;
		}
		tmp = finallyEnd;

		// collect finally-block tokens
		TokenList finallyTokens;
		while ( finallyBegin != finallyEnd ) {
			finallyTokens.push_back((*finallyBegin));
			finallyBegin++;
		}

		mControlFlow = interpret(finallyTokens, result);
	}
}

void Interpreter::process_type(TokenIterator& token)
{
	bool isConst = false;
	bool isFinal = false;

	std::string name;
	std::string prototype;
	std::string type;
	std::string value;

	if ( token->type() == Token::Type::PROTOTYPE ) {
		prototype = token->content();
		token++;
	}

	type = token->content();
	token++;
	name = token->content();

	expect(Token::Type::IDENTIFER, token);

	token++;

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

	Object *object = static_cast<Object*>(resolve(name, true));
	if ( object ) {
		throw Utils::Exceptions::DuplicateIdentifer("process_type: " + name, token->position());
	}

	object = mRepository->createInstance(type, name, prototype);

	define(name, object);

	if ( isConst ) object->setConst(true);
	if ( isFinal ) object->setFinal(true);

	if ( assign != getTokens().end() ) {
		TokenIterator end = findNext(assign, Token::Type::SEMICOLON);

		expression(object, assign);

		token = end;
	}

	expect(Token::Type::SEMICOLON, token);
}

// syntax:
// while ( <condition> ) {
// ...
// }
void Interpreter::process_while(TokenIterator& token, Object *result)
{
	// find next open parenthesis
	TokenIterator condBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);
	// find next open curly bracket '{'
	TokenIterator bodyBegin = findNext(condEnd, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	token = bodyEnd;
	if ( bodyEnd != getTokens().end() ) {
		bodyEnd++;
	}

	TokenList statementTokens;
	while ( bodyBegin != bodyEnd ) {
		statementTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		TokenIterator tmp = condBegin;

		Object condition;
		expression(&condition, tmp);

		if ( !isTrue(condition) ) {
			break;
		}

		ControlFlow::E controlflow = interpret(statementTokens, result);

		switch ( controlflow ) {
			case ControlFlow::Break: mControlFlow = ControlFlow::Normal; return;
			case ControlFlow::Continue: mControlFlow = ControlFlow::Normal; continue;
			case ControlFlow::Normal: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::Return: mControlFlow = ControlFlow::Return; return;
			case ControlFlow::Throw: mControlFlow = ControlFlow::Throw; return;
		}
	}
}

void Interpreter::pushTokens(const TokenList& tokens)
{
	mTokenStack.push_back(tokens);
}

Symbol* Interpreter::resolve(const std::string& name, bool onlyCurrentScope) const
{
	std::string member, parent;
	Tools::split(name, parent, member);

	Symbol *result = LocalScope::resolve(parent, onlyCurrentScope);

	while ( result && !member.empty() ) {
		switch ( result->getType() ) {
			case Symbol::IType::AtomicTypeSymbol:
			case Symbol::IType::ObjectSymbol:
				result = static_cast<Object*>(result)->resolve(member);
				break;
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::NamespaceSymbol:
				return result;
			case Symbol::IType::BluePrintSymbol:
			case Symbol::IType::UnknownSymbol:
				throw Utils::Exceptions::SyntaxError("cannot directly access locales of method/namespace");
		}

		Tools::split(member, parent, member);
	}

	return result;
}

Symbol* Interpreter::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	std::string member, parent;
	Tools::split(name, parent, member);

	if ( member.empty() ) {
		member = parent;
		parent = KEYWORD_THIS;
	}

	Symbol *result = LocalScope::resolve(parent, onlyCurrentScope);

	if ( result ) {
		switch ( result->getType() ) {
			case Symbol::IType::AtomicTypeSymbol:
			case Symbol::IType::ObjectSymbol:
				return static_cast<Object*>(result)->resolveMethod(member, params, onlyCurrentScope);
			case Symbol::IType::MethodSymbol:
				return result;
			case Symbol::IType::BluePrintSymbol:
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::UnknownSymbol:
				throw Utils::Exceptions::SyntaxError("cannot directly access locales of method/namespace");
		}
	}

	return 0;
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
