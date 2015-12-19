
// Header
#include "Interpreter.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Helpers/Math.h>
#include <Core/Helpers/Strings.h>
#include <Core/Interfaces/IPrinter.h>
#include <Core/OperatorOverloading.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Core/Helpers/BooleanEvaluations.h>
#include <Core/Helpers/Math.h>
#include "Memory.h"
#include "Object.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Interpreter::Interpreter()
: mMemory(0),
  mRepository(0)
{
}

Interpreter::~Interpreter()
{
}

void Interpreter::addIdentifier(Object object)
{
	assert(!"implement me");
/*
	if ( mLocales.find(object.name()) != mLocales.end() ) {
		if ( object.isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw DuplicateIdentifer(object.name());
	}

	mLocales[object.name()] = object;
*/
}

TokenIterator Interpreter::consumeToken()
{
	mTokens.pop_front();

	return mTokens.begin();
}

Object* Interpreter::getSymbol(const std::string& token)
{
(void)token;
	return 0;
}

Object Interpreter::parseCondition(TokenIterator& token)
{
	Object v1 = parseExpression(token);

	for ( ; ; ) {
		Token::Type::E op = token->type();
		if ( op != Token::Type::COMPARE_EQUAL && op != Token::Type::COMPARE_GREATER && op != Token::Type::COMPARE_GREATER_EQUAL &&
			op != Token::Type::COMPARE_LESS && op != Token::Type::COMPARE_LESS_EQUAL ) {
				return v1;
		}

		// consume operator token
		token++;

		Object v2 = parseExpression(token);

		if ( op == Token::Type::COMPARE_EQUAL ) {
			v1.setValue( (v1.getValue() == v2.getValue()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_GREATER ) {
			v1.setValue( (v1.getValue() > v2.getValue()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_GREATER_EQUAL ) {
			v1.setValue( (v1.getValue() >= v2.getValue()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_LESS ) {
			v1.setValue( (v1.getValue() < v2.getValue()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_LESS_EQUAL ) {
			v1.setValue( (v1.getValue() <= v2.getValue()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_UNEQUAL ) {
			v1.setValue( (v1.getValue() != v2.getValue()) ? "true" : "false" );
		}
	}

	return v1;
}

Object Interpreter::parseExpression(TokenIterator& start)
{
	// parse summands

	Object v1 = parseFactors(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::BITAND &&
			 op != Token::Type::BITOR &&
			 op != Token::Type::MATH_ADD &&
			 op != Token::Type::MATH_SUBTRACT ) {
			return v1;
		}

		// consume operator token
		start++;

		Object v2;
		parseFactors(&v2, start);

		if ( op == Token::Type::BITAND ) {
			operator_bitand(&v1, &v2);
		}
		else if ( op == Token::Type::BITOR ) {
			operator_bitor(&v1, &v2);
		}
		else if ( op == Token::Type::MATH_ADD ) {
			operator_plus(&v1, &v2);
		}
		else if ( op == Token::Type::MATH_SUBTRACT ) {
			operator_subtract(&v1, &v2);
		}
		else {
			throw Utils::Exceptions::SyntaxError("unexpected token " + start->content() + " found");
		}
	}

	return v1;
}

Object Interpreter::parseFactors(TokenIterator& start)
{
	Object v1;
	if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
		start++;
		v1 = parseExpression(start);

		if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
			// ups...
		}

		start++;
	}
	else {
		v1 = parseTerm(start);
	}

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIV &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTI ) {
			return v1;
		}

		// consume operator token
		start++;

		Object v2;
		if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
			start++;
			v2 = parseExpression(start);

			if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
				// ups...
			}

			start++;
		}
		else {
			v2 = parseTerm(start);
		}

		if ( op == Token::Type::MATH_DIV ) {
			operator_divide(&v1, &v2);
		}
		else if ( op == Token::Type::MATH_MODULO ) {
			operator_modulo(&v1, &v2);
		}
		else if ( op == Token::Type::MATH_MULTI ) {
			operator_multiply(&v1, &v2);
		}
		else {
			throw Utils::Exceptions::SyntaxError("unexpected token " + start->content() + " found");
		}
	}

	return v1;
}

Object Interpreter::parseTerm(TokenIterator& start)
{
	Object result;

	switch ( start->type() ) {
		case Token::Type::CONST_BOOLEAN: {
			result = Bool(start->content());
		} break;
		case Token::Type::CONST_NUMBER: {
			result = Number(start->content());
		} break;
		case Token::Type::IDENTIFER: {
			// find out if we have to execute a method
			// or simply get a stored variable
/*
			if ( isLocalSymbol(start->content()) ) {
				result = getSymbol(start->content());
			}
			if ( isMember(start->content()) ) {
				result = getSymbol(start->content());
			}
			else if ( isMethod(start->content()) ) {
				result = process_method(start);
			}
			else {
				throw Utils::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}
*/
			Object *obj = getSymbol(start->content());
			if ( obj ) {
				result = (*obj);
			}
		} break;
		case Token::Type::KEYWORD: {
			result = process();
		} break;
		case Token::Type::CONST_LITERAL: {
			result = String(start->content());
		} break;
		default: {
			throw Utils::Exceptions::SyntaxError("identifier, literal or number expected but " + start->content() + " as " + Token::Type::convert(start->type()) + " found", start->position());
		} break;
	}

	start++;
	return result;
}

Object Interpreter::process()
{
	TokenIterator token = consumeToken();

	Object result;

	// go through all keywords and if we find the one
	// that we want to execute, redirect to the corresponding method
	while ( token != mTokens.end() ) {
		// decide what we want to do according to
		// the type of token we have
		switch ( token->type() ) {
			case Token::Type::CONST_BOOLEAN:
			case Token::Type::CONST_FLOAT:
			case Token::Type::CONST_INTEGER:
			case Token::Type::CONST_LITERAL:
			case Token::Type::CONST_NUMBER:
				//parseExpression(token);
				break;
			case Token::Type::IDENTIFER: {
				//process_assign(token);
			} break;
			case Token::Type::KEYWORD: {
				if ( token->content() == "new" ) {
					//return (*mMemory->getObject(process_new(token)));
				}
				else if ( token->content() == "return" ) {
					//return parseExpression(++token);
				}
				else {
					//process_keyword(token);
				}
			} break;
			case Token::Type::PROTOTYPE:
			case Token::Type::TYPE:
				//process_type(token);
				break;
			default:
				//Printer::print("invalid token '" + token->content() + "' as type " + Token::Type::convert(token->type()) + " found!");
				break;
		}

		token = consumeToken();
	}

	return result;
}


// syntax:
// assert(<condition>);
void Interpreter::process_assert(TokenIterator& token)
{
	// find next open parenthesis
	TokenIterator condBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN, Token::Type::SEMICOLON);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin, 0, Token::Type::SEMICOLON);
	// find semicolon
	TokenIterator tmp = findNext(condEnd, Token::Type::SEMICOLON);

	Object condition = parseCondition(condBegin);

	if ( isFalse(condition) ) {
		throw Utils::Exceptions::AssertionFailed("'" + condition.getValue() + "'", token->position());
	}

	token = tmp;
}

// syntax:
// new <Object>([<parameter list>]);
Object Interpreter::process_new(TokenIterator& token)
{
	TokenIterator tmp = token;

	bool isPrototype = token->type() == Token::Type::PROTOTYPE;
	std::string name = "<temporary object>";
	std::string prototype = token->content();

	if ( isPrototype ) {
		token++;
	}

	std::string type = token->content();

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	ParameterList params;

	tmp = opened;
	// loop through all parameters seperated by colons
	while ( tmp != closed ) {
		Object v = parseExpression(tmp);
		params.push_back(Parameter(v.getName(), v.Typename(), v.getValue(), Parameter::AccessMode::ByValue));

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

	return object;
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

	/*Object v =*/ parseExpression(opened);
	//Printer::print(v.value() + "   [" + mOwner->Filename() + ":" + Tools::toString(token->position().line) + "]");

	token = tmp;
}

void Interpreter::process_type(TokenIterator& token)
{
	bool isConst = false;
	bool isPrototype = token->type() == Token::Type::PROTOTYPE;
	bool isStatic = false;

	std::string name;
	std::string prototype;
	std::string value;

	if ( isPrototype ) {
		prototype = token->content();
		token++;
	}

	std::string type = token->content();
	token++;
	name = token->content();

	if ( token->type() != Token::Type::IDENTIFER ) {
		throw Utils::Exceptions::SyntaxError("identifier expected but '" + token->content() + "' found", token->position());
	}

	token++;

	std::string tmpStr = token->content();
	if ( tmpStr == "const" || tmpStr == "static" ) {
		token++;

		if ( tmpStr == "const" ) {
			isConst = true;
		}
		else if ( tmpStr == "static" ) {
			isStatic = true;
		}
	}

	TokenIterator assign = mTokens.end();
	if ( token->type() == Token::Type::ASSIGN ) {
		assign = ++token;
	}

	Object object = mRepository->createInstance(type, name, prototype);

	if ( isConst ) object.setConst(true);
	if ( isStatic ) object.setStatic(true);

	if ( assign != mTokens.end() ) {
		object.setValue(parseExpression(assign).value());
		token = assign;
	}

	addIdentifier(object);


	if ( token->type() != Token::Type::SEMICOLON ) {
		throw Utils::Exceptions::SyntaxError("';' expected but '" + token->content() + "' found", token->position());
	}
}

void Interpreter::setMemory(Memory *memory)
{
	mMemory = memory;
}

void Interpreter::setScope(const std::string& scope)
{
	mScope = scope;
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
