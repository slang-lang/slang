
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
#include <Core/Helpers/Math.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Printer.h>
#include "Memory.h"
#include "Object.h"
#include "OperatorOverloading.h"
#include "Repository.h"
#include "System.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Interpreter::Interpreter(IScope *scope, const std::string& name)
: LocalScope(name, scope),
  mControlFlow(ControlFlow::None),
  mRepository(0)
{
}

Interpreter::~Interpreter()
{
}

Interpreter::ControlFlow::E Interpreter::execute(Object *result)
{
	mControlFlow = ControlFlow::None;		// reset this every time we start executing a method

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
		else if ( op == Token::Type::OR && isFalse(*result) ) {
			*result = BoolObject(isTrue(*result) || isTrue(v2));
		}
	}
}

void Interpreter::garbageCollector(bool /*force*/)
{
	//for ( Symbols::iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
/*
	Symbols::iterator it = mSymbols.begin();
	while ( it != mSymbols.end() ) {
		Symbol *symbol = it->second;

		if ( symbol->getType() == Symbol::IType::ObjectSymbol ) {
			mRepository->removeReference(static_cast<Object*>(symbol));
		}
		else {
			delete symbol;
		}

		it = mSymbols.erase(it);
	}
	mSymbols.clear();
*/
}

const TokenList& Interpreter::getTokens() const
{
	return mTokenStack.back();
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

		// consume comperator token
		start++;

		Object v2;
		parseExpression(&v2, start);

		if ( op == Token::Type::COMPARE_EQUAL ) {
			*result = BoolObject(operator_equal(result, &v2));
		}
		else if ( op == Token::Type::COMPARE_GREATER ) {
			*result = BoolObject(operator_greater(result, &v2));
		}
		else if ( op == Token::Type::COMPARE_GREATER_EQUAL ) {
			*result = BoolObject(operator_greater_equal(result, &v2));
		}
		else if ( op == Token::Type::COMPARE_LESS ) {
			*result = BoolObject(operator_less(result, &v2));
		}
		else if ( op == Token::Type::COMPARE_LESS_EQUAL ) {
			*result = BoolObject(operator_less_equal(result, &v2));
		}
		else if ( op == Token::Type::COMPARE_UNEQUAL ) {
			*result = BoolObject(!operator_equal(result, &v2));
		}
	}
}

void Interpreter::parseExpression(Object *result, TokenIterator& start)
{
	parseFactors(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::BITAND &&
			 op != Token::Type::BITOR &&
			 op != Token::Type::MATH_ADD &&
			 op != Token::Type::MATH_SUBTRACT ) {
			return;
		}

		// consume operator token
		start++;

		Object v2;
		parseFactors(&v2, start);

		if ( op == Token::Type::BITAND ) {
			operator_bitand(result, &v2);
		}
		else if ( op == Token::Type::BITOR ) {
			operator_bitor(result, &v2);
		}
		else if ( op == Token::Type::MATH_ADD ) {
			operator_plus(result, &v2);
		}
		else if ( op == Token::Type::MATH_SUBTRACT ) {
			operator_subtract(result, &v2);
		}
	}
}

void Interpreter::parseFactors(Object *result, TokenIterator& start)
{
	if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
		start++;
		expression(result, start);

		if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
			throw Utils::Exceptions::SyntaxError("')' expected but "  + start->content() + " found", start->position());
		}

		start++;
	}
	else {
		parseTerm(result, start);
	}

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIVIDE &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTIPLY ) {
			return;
		}

		// consume operator token
		start++;

		Object v2;
		if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
			start++;
			expression(&v2, start);

			if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
				throw Utils::Exceptions::SyntaxError("')' expected but "  + start->content() + " found", start->position());
			}

			start++;
		}
		else {
			parseTerm(&v2, start);
		}

		if ( op == Token::Type::MATH_DIVIDE ) {
			operator_divide(result, &v2);
		}
		else if ( op == Token::Type::MATH_MODULO ) {
			operator_modulo(result, &v2);
		}
		else if ( op == Token::Type::MATH_MULTIPLY ) {
			operator_multiply(result, &v2);
		}
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
			if ( symbol ) {
				switch ( symbol->getType() ) {
					case Symbol::IType::MethodSymbol:
						process_method(start, result);
						break;
					case Symbol::IType::AtomicTypeSymbol:
					case Symbol::IType::MemberSymbol:
					case Symbol::IType::ObjectSymbol:
						*result = *static_cast<Object*>(symbol);
						break;
					case Symbol::IType::NamespaceSymbol:
					case Symbol::IType::UnknownSymbol:
						break;
				}
			}
		} break;
		case Token::Type::KEYWORD: {
			process(result, start, getTokens().end(), Token::Type::SEMICOLON);
		} break;
		case Token::Type::MATH_SUBTRACT: {
			throw Utils::Exceptions::NotImplemented("unary minus");
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

		if ( mControlFlow != ControlFlow::None ) {
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
				process_identifier(token, terminator == Token::Type::NIL ? Token::Type::SEMICOLON : terminator);
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
				throw Utils::Exceptions::SyntaxError("invalid token '" + token->content() + "' as type " + Token::Type::convert(token->type()) + " found", token->position());
				break;
		}

		token++;	// consume token
	}
}

// syntax:
// assert [(] <expression> [)];
void Interpreter::process_assert(TokenIterator& token)
{
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
void Interpreter::process_break(TokenIterator& token)
{
	//System::Print(KEYWORD_BREAK, token->position());

(void)token;
	mControlFlow = ControlFlow::Break;
}

// syntax:
// continue;
void Interpreter::process_continue(TokenIterator& token)
{
	//System::Print(KEYWORD_CONTINUE, token->position());

(void)token;
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
		case Symbol::IType::MemberSymbol:
		case Symbol::IType::ObjectSymbol:
			mRepository->removeReference(static_cast<Object*>(symbol));
			break;
		case Symbol::IType::MethodSymbol:
		case Symbol::IType::NamespaceSymbol:
		case Symbol::IType::UnknownSymbol:
			throw Utils::Exceptions::TypeMismatch("member or local variable expected but " + symbol->getName() + " found", token->position());
			break;
	}

	token = end;
}

// syntax:
// for ( <expression>; <condition>; <expression> ) { }
// i.e. for ( int i = 0; i < 5; i += 1 ) {
// ...
// }
void Interpreter::process_for(TokenIterator& token)
{
	// find declaration
	TokenIterator declarationBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find condition
	const TokenIterator conditionBegin = ++findNext(declarationBegin, Token::Type::SEMICOLON);
	// find expression
	const TokenIterator expressionBegin = ++findNext(conditionBegin, Token::Type::SEMICOLON);
	// find next open curly bracket '{'
	TokenIterator expressionEnd = findNext(expressionBegin, Token::Type::PARENTHESIS_CLOSE);

	if ( expressionEnd != getTokens().end() ) {
		expressionEnd++;
	}

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyBegin = findNext(expressionBegin, Token::Type::BRACKET_CURLY_OPEN);
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	// process our declaration part
	Object declaration;
	process(&declaration, declarationBegin, conditionBegin, Token::Type::SEMICOLON);

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
		mControlFlow = ControlFlow::None;

		TokenIterator condBegin = conditionBegin;

		Object condition;
		expression(&condition, condBegin);

		if ( isFalse(condition) ) {
			break;
		}
		// }

		// Body parsing
		// {
		mControlFlow = ControlFlow::None;

		pushTokens(loopTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			VoidObject tmp;
			process(&tmp, tmpBegin, tmpEnd);
		}
		popTokens();

		if ( mControlFlow == ControlFlow::Break ) {
			break;
		}
		else if ( mControlFlow == ControlFlow::Continue ) {
			continue;
		}
		else if ( mControlFlow == ControlFlow::Return ) {
			return;
		}
		// }

		// Expression parsing
		// {
		mControlFlow = ControlFlow::None;

		TokenIterator exprBegin = expressionBegin;
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
void Interpreter::process_identifier(TokenIterator& token, Token::Type::E terminator)
{
	// try to find assignment token
	TokenIterator assign = findNext(token, Token::Type::ASSIGN, terminator);//Token::Type::SEMICOLON);
	// find next semicolon
	TokenIterator end = findNext(assign, terminator);//Token::Type::SEMICOLON);

    if ( assign == token ) {
        // we don't have an assignment but a method call
		Object tmp;
		expression(&tmp, token);

        token = end;
        return;
    }

	std::string identifier = token->content();

	Object *symbol = static_cast<Object*>(resolve(identifier));
	if ( !symbol ) {
		throw Utils::Exceptions::UnknownIdentifer("identifier '" + identifier + "' not found", token->position());
	}
	if ( symbol->isConst() ) {
		throw Utils::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + identifier + "'", token->position());
	}
/*
	if ( isMember(identifier) && (this->isConst() || mOwner->isConst()) ) {
		throw Utils::Exceptions::ConstCorrectnessViolated("tried to modify member '" + identifier + "' in const method '" + getScopeName() + "'", token->position());
	}
*/

	expression(symbol, ++assign);

	if ( symbol->isFinal() && symbol->isModifiable() ) {
		// we have modified a final entity for the first time, we now have to set it so const
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
void Interpreter::process_if(TokenIterator& token)
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
		pushTokens(ifTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			VoidObject tmp;
			process(&tmp, tmpBegin, tmpEnd);
		}
		popTokens();
	}
	else if ( !elseTokens.empty() ) {
		pushTokens(elseTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			VoidObject tmp;
			process(&tmp, tmpBegin, tmpEnd);
		}
		popTokens();
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
		process_for(token);
	}
	else if ( keyword == KEYWORD_IF ) {
		process_if(token);
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
		process_switch(token);
	}
	else if ( keyword == KEYWORD_WHILE ) {
		process_while(token);
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
		params.push_back(Parameter(obj->getName(), obj->Typename(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj));

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

	Symbol *symbol = resolve(method);
	if ( symbol ) {
		switch ( symbol->getType() ) {
			case Symbol::IType::MethodSymbol:
				static_cast<Method*>(symbol)->execute(params, result);
				return;
			case Symbol::IType::AtomicTypeSymbol:
			case Symbol::IType::MemberSymbol:
			case Symbol::IType::ObjectSymbol:
				*result = *static_cast<Object*>(symbol);
				return;
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::UnknownSymbol:
				break;
		}
	}

	throw Utils::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + method + "' found", tmp->position());
}

// syntax:
// new <Object>([<parameter list>]);
void Interpreter::process_new(TokenIterator& token, Object *result)
{
	TokenIterator tmp = token;

	std::string name = "<temporary object>";
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
		params.push_back(Parameter(obj->getName(), obj->Typename(), obj->getValue(), false, obj->isConst(), Parameter::AccessMode::Unspecified, obj));

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

	assert(mRepository);

	Object *object = mRepository->createInstance(type, name, prototype);
	object->connectRepository(mRepository);
	object->Constructor(params);

	*result = *object;

	//mRepository->removeReference(object);
}

// syntax:
// print(<expression>);
void Interpreter::process_print(TokenIterator& token)
{
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
void Interpreter::process_scope(TokenIterator& token, Object* /*result*/)
{
	TokenIterator scopeBegin = ++token;
	TokenIterator scopeEnd = findNextBalancedCurlyBracket(scopeBegin, getTokens().end());

	TokenList tmpTokens;
	while ( scopeBegin != scopeEnd ) {
		tmpTokens.push_back((*scopeBegin));
		scopeBegin++;
	}

/*
	Method scope(this, getName(), getTypeName());
	scope.setConst(this->isConst());
	scope.setFinal(this->isFinal());
	scope.setLanguageFeatureState(this->languageFeatureState());
	scope.setRepository(this->mRepository);
	scope.setStatic(this->isStatic());
	scope.setTokens(tmpTokens);
	scope.visibility(this->visibility());

	scope.execute(ParameterList(), result);

	this->mControlFlow = scope.mControlFlow;
*/

	Interpreter interpreter(this, getScopeName());
	interpreter.setRepository(mRepository);
	interpreter.setTokens(tmpTokens);

	Object tmp;
	mControlFlow = interpreter.execute(&tmp);

	token = scopeEnd;
}

// syntax:
// switch ( <expression> ) {
//		case <identifier>:
//			...
//		break;
// }
void Interpreter::process_switch(TokenIterator& token)
{
throw Utils::Exceptions::NotImplemented("switch-case");

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

	TokenList switchTokens;
	while ( bodyBegin != bodyEnd ) {
		switchTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	TokenIterator tmp = condBegin;

	Object value;
	expression(&value, tmp);

	pushTokens(switchTokens);
	{
		TokenIterator tmpBegin = getTokens().begin();
		TokenIterator tmpEnd = getTokens().end();

		VoidObject result;
		process(&result, tmpBegin, tmpEnd);
	}
	popTokens();
}

void Interpreter::process_type(TokenIterator& token)
{
	bool isConst = false;
	bool isFinal = false;
	bool isStatic = false;

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

	if ( token->type() != Token::Type::IDENTIFER ) {
		throw Utils::Exceptions::SyntaxError("identifier expected but '" + token->content() + "' found", token->position());
	}

	token++;

	std::string tmpStr = token->content();
	if ( tmpStr == MODIFIER_CONST || tmpStr == MODIFIER_STATIC ) {
		token++;

		if ( tmpStr == MODIFIER_CONST ) { isConst = true; }
		else if ( tmpStr == MODIFIER_FINAL ) { isFinal = true; }
		else if ( tmpStr == MODIFIER_STATIC ) { isStatic = true; }
	}

	TokenIterator assign = getTokens().end();
	if ( token->type() == Token::Type::ASSIGN ) {
		assign = ++token;
	}

	Object *object = static_cast<Object*>(resolve(name, true));
	if ( !object ) {
		object = mRepository->createInstance(type, name, prototype);

		if ( isConst ) object->setConst(true);
		if ( isFinal ) object->setFinal(true);
		if ( isStatic ) object->setStatic(true);

		if ( assign != getTokens().end() ) {
			TokenIterator end = findNext(assign, Token::Type::SEMICOLON);

			expression(object, assign);

			token = end;
		}

		define(name, object);

		if ( token->type() != Token::Type::SEMICOLON ) {
			throw Utils::Exceptions::SyntaxError("';' expected but '" + token->content() + "' found", token->position());
		}
	}
	else {
		if ( !object->isStatic() ) {
			// upsi, did not clean up..
			throw Utils::Exceptions::DuplicateIdentifer("process_type: " + name, token->position());
		}

		token = findNext(token, Token::Type::SEMICOLON);
	}
}

// syntax:
// while ( <condition> ) {
// ...
// }
void Interpreter::process_while(TokenIterator& token)
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

	TokenList whileTokens;
	while ( bodyBegin != bodyEnd ) {
		whileTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		mControlFlow = ControlFlow::None;

		TokenIterator tmp = condBegin;

		Object condition;
		expression(&condition, tmp);

		if ( isFalse(condition) ) {
			break;
		}

		pushTokens(whileTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			VoidObject result;
			process(&result, tmpBegin, tmpEnd);
		}
		popTokens();

		if ( mControlFlow == ControlFlow::Break ) {
			break;
		}
		else if ( mControlFlow == ControlFlow::Continue ) {
			continue;
		}
		else if ( mControlFlow == ControlFlow::Return ) {
			return;
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
			case Symbol::IType::MemberSymbol:
			case Symbol::IType::ObjectSymbol:
				result = static_cast<Object*>(result)->resolve(member);
				break;
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::NamespaceSymbol:
				return result;
			case Symbol::IType::UnknownSymbol:
				throw Utils::Exceptions::SyntaxError("cannot directly access locales of method/namespace");
		}

		Tools::split(member, parent, member);
	}

	return result;
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