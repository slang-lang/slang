
// Header
#include "Method.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/BuildInObjects/Bool.h>
#include <Core/BuildInObjects/Number.h>
#include <Core/BuildInObjects/String.h>
#include <Core/Interfaces/IPrinter.h>
#include "Exceptions.h"
#include "Object.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Method::Method(const std::string& name, const std::string& type)
: Variable(name, type),
  mOwner(0),
  mRepository(0)
{
}

Method::~Method()
{
	garbageCollector();
}

void Method::addIdentifier(Object v)
{
	if ( mVariables.find(v.name()) != mVariables.end() ) {
		if ( v.isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw DuplicateIdentifer(v.name());
	}

/*
	mVariables.insert(
		std::make_pair<std::string, Object>(v.name(), v)
	);
*/
	mVariables[v.name()] = v;
}

Object Method::execute(const VariablesList& params)
{
	if ( !isSignatureValid(params) ) {
		throw ParameterCountMissmatch("number or type of parameters incorrect");
	}

	VariablesList::const_iterator rIt = mSignature.begin();
	// add parameters as pseudo members
	for ( VariablesList::const_iterator it = params.begin(); it != params.end(); ++it, ++rIt ) {
		Object v((*rIt).name(), "", (*it).type(), (*it).value());

		addIdentifier(v);
	}

	Object returnValue(name(), "", type(), "");
	returnValue.visibility(visibility());

	try {	// try to execute our method
		TokenIterator start = mTokens.begin();
		Object r = process(start, mTokens.end());
		returnValue.assign(r);
	}
	catch ( Exception &e ) {	// if any thing happens clean up the mess
		garbageCollector();

		// throw again so that our owner will be informed
		throw e;
	}

	// after we gathered our result
	// let the garbage collector do it's magic
	garbageCollector();

	return returnValue;
}

void Method::garbageCollector()
{
	// clean up local stuff
	mStack.clear();

	MemberMap tmp;
	for ( MemberMap::iterator varIt = mVariables.begin(); varIt != mVariables.end(); ++varIt ) {
		if ( varIt->second.isStatic() ) {
			tmp.insert((*varIt));
		}
	}

	mVariables.clear();
	mVariables = tmp;
}

Object& Method::getVariable(const std::string& name)
{
	for ( MemberMap::iterator it = mVariables.begin(); it != mVariables.end(); ++it ) {
		if ( it->first == name ) {
			return it->second;
		}
	}

	Object& o = mOwner->getMember(name);
	if ( o.name() != "" ) {
		return o;
	}

	throw SyntaxError("expected identifier but '" + name + "' found!");
}

void Method::handleType(TokenIterator& token)
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
		throw SyntaxError("identifier expected but '" + token->content() + "' found", token->position());
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

	Object object;
	if ( isPrototype ) {
		object = mRepository->createInstanceFromPrototype(prototype, type, name);
	}
	else {
		object = mRepository->createInstance(type, name);
	}

	if ( isConst ) object.setConst(true);
	if ( isStatic ) object.setStatic(true);

	if ( assign != mTokens.end() ) {
		object.assign(parseExpression(assign));
		token = assign;
	}

	addIdentifier(object);

	if ( token->type() != Token::Type::SEMICOLON ) {
		throw SyntaxError("';' expected but '" + token->content() + "' found", token->position());
	}
}

bool Method::isBooleanConst(const std::string& v) const
{
	return ( v == "false" || v == "true" );
}

bool Method::isFalse(const std::string& s) const
{
	return (s == "false");
}

bool Method::isFalse(const Object& v) const
{
	if ( v.value() == "0" || v.value() == "false" ) {
		return true;
	}

	return false;
}

bool Method::isLocal(const std::string& token)
{
	std::string member, parent;
	Tools::split(token, parent, member);

	// check if token is a local variable
	// OR
	// loop through all locals and ask them if this identifier belongs to them
	for ( MemberMap::iterator it = mVariables.begin(); it != mVariables.end(); ++it ) {
		if ( it->first == token ) {
			return true;
		}

		if ( it->second.name() == parent ) {
			if ( it->second.hasMember(member) ) {
				return true;
			}
		}
	}

	return false;
}

bool Method::isMember(const std::string& token)
{
	// check if token is a member variable
	return mOwner->hasMember(token);
}

bool Method::isMethod(const std::string& token)
{
	// check if token is a method of our parent object
	return mOwner->hasMethod(token);
}

bool Method::isMethod(const std::string& token, const VariablesList& params)
{
	// check if token is a method of our parent object
	return mOwner->hasMethod(token, params);
}

bool Method::isSignatureValid(const VariablesList& params) const
{
	// check method signature by:
	// 1) comparing the number of parameters
	if ( mSignature.size() != params.size() ) {
		return false;
	}

	// 2) by comparing their types
	VariablesList::const_iterator pIt = params.begin();
	for ( VariablesList::const_iterator it = mSignature.begin(); it != mSignature.end(); ++it, ++pIt ) {
		if ( (*it).type() != (*pIt).type() ) {
			return false;
		}
	}

	// no difference was found
	return true;
}

bool Method::isTrue(const std::string& s) const
{
	return (s == "true");
}

bool Method::isTrue(const Object& v) const
{
	// check value is false
	if ( v.value() == "0" || v.value() == "0.0" || v.value() == "false" ) {
		return false;
	}

	// value is not false, so return true
	return true;
}

Object Method::math_add(const Object& v1, const Object& v2)
{
	Object result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 + f2));
	}
	else {
		//throw TypeMismatch("for addition: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw TypeMismatch("for addition: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Object Method::math_divide(const Object& v1, const Object& v2)
{
	Object result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 / f2));
	}
	else {
		//throw TypeMismatch("for division: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw TypeMismatch("for division: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Object Method::math_multiply(const Object& v1, const Object& v2)
{
	Object result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 * f2));
	}
	else {
		//throw TypeMismatch("for multiplication: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw TypeMismatch("for multiplication: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Object Method::math_subtract(const Object& v1, const Object& v2)
{
	Object result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 - f2));
	}
	else {
		//throw TypeMismatch("for subtraction: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw TypeMismatch("for subtraction: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Object Method::parseAtom(TokenIterator& start)
{
	Object v;

	switch ( start->type() ) {
		case Token::Type::BOOLEAN: {
			v = Bool(start->content());
		} break;
		case Token::Type::CONSTANT: {
			v = Number(start->content());
		} break;
		case Token::Type::IDENTIFER: {
			// find out if we have to execute a method
			// or simple get a stored variable
			if ( isLocal(start->content()) ) {
				v.assign(getVariable(scope(start->content())));
			}
			else if ( isMember(start->content()) ) {
				v.assign(getVariable(start->content()));
			}
			else if ( isMethod(start->content()) ) {
				v.assign(process_method(start));
			}
			else {
				throw UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}
		} break;
		case Token::Type::KEYWORD: {
			v.assign(process(start, mTokens.end(), Token::Type::SEMICOLON));
		} break;
		case Token::Type::LITERAL: {
			v = String(start->content());
		} break;
		default:
			throw SyntaxError("identifier, literal or number expected but " + start->content() + " as " + Token::Type::convert(start->type()) + " found", start->position());
			break;
	}

	start++;
	return v;
}

Object Method::parseCondition(TokenIterator& token)
{
	//Object v1 = parseExpression(token);
	Object v1;
	v1.assign(parseExpression(token));

	for ( ; ; ) {
		Token::Type::E op = token->type();
		if ( op != Token::Type::COMPARE_EQUAL && op != Token::Type::COMPARE_GREATER && op != Token::Type::COMPARE_GREATER_EQUAL &&
			op != Token::Type::COMPARE_LESS && op != Token::Type::COMPARE_LESS_EQUAL ) {
				return v1;
		}

		token++;
		Object v2 = parseExpression(token);

		if ( op == Token::Type::COMPARE_EQUAL ) {
			v1.value( (v1.value() == v2.value()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_GREATER ) {
			v1.value( (v1.value() > v2.value()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_GREATER_EQUAL ) {
			v1.value( (v1.value() >= v2.value()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_LESS ) {
			v1.value( (v1.value() < v2.value()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_LESS_EQUAL ) {
			v1.value( (v1.value() <= v2.value()) ? "true" : "false" );
		}
		else if ( op == Token::Type::COMPARE_UNEQUAL ) {
			v1.value( (v1.value() != v2.value()) ? "true" : "false" );
		}
	}
}

Object Method::parseExpression(TokenIterator& start)
{
	//Object result = parseSummands(start);
	Object result;
	result.assign(parseSummands(start));
	return result;
}

Object Method::parseFactors(TokenIterator& start)
{
	//Object v1 = parseAtom(start);
	Object v1;
	v1.assign(parseAtom(start));

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_MULTI && op != Token::Type::MATH_DIV ) {
			return v1;
		}

		start++;
		Object v2 = parseAtom(start);

		if ( op == Token::Type::MATH_MULTI ) {
			v1 = math_multiply(v1, v2);
		}
		else {
			v1 = math_divide(v1, v2);
		}
	}
}

Object Method::parseSummands(TokenIterator& start)
{
	//Object v1 = parseAtom(start);
	Object v1;
	v1.assign(parseAtom(start));

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_ADD && op != Token::Type::MATH_SUBTRACT &&
			 op != Token::Type::STRING_ADD ) {
			return v1;
		}

		start++;
		Object v2 = parseFactors(start);

		if ( op == Token::Type::MATH_ADD ) {
			v1 = math_add(v1, v2);
		}
		else if ( op == Token::Type::MATH_SUBTRACT ) {
			v1 = math_subtract(v1, v2);
		}
		else if ( op == Token::Type::STRING_ADD ) {
			v1 = string_concat(v1, v2);
		}
	}
}

void Method::pop_stack()
{
	mStack.pop_back();
}

Object Method::process(TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	Object returnValue;

	// go through all keywords and if we find the one
	// that we want to execute, redirect to the corresponding method
	while ( token != end && token->type() != terminator && token->type() != Token::Type::ENDOFFILE ) {
		// decide what we want to do according to
		// the type of token we have
		switch ( token->type() ) {
			case Token::Type::BOOLEAN: {
				parseExpression(token);
			} break;
			case Token::Type::CONSTANT: {
				parseExpression(token);
			} break;
			case Token::Type::IDENTIFER: {
				// try to find assignment token
				TokenIterator assign = findNext(token, Token::Type::ASSIGN, Token::Type::SEMICOLON);
				// find next semicolon
				TokenIterator end = findNext(token, Token::Type::SEMICOLON);

				if ( assign == token ) {
					// we don't have an assignment but a method call
					parseExpression(token);

					token = end;
					break;
				}

				bool found = false;

				if ( isLocal(token->content()) ) {
					found = true;
				}
				else if ( isMember(token->content()) ) {
					found = true;
				}
				else {
					throw UnknownIdentifer(token->content(), token->position());
				}

				Object& s = getVariable(token->content());
				Object t = parseExpression(++assign);

				if ( s.isConst() || (this->isConst() && isMember(s.name())) ) {
					throw Exception("can not change const object!", token->position());
				}

				s.assign(t);

				// assign == end should now be true
				token = end;
				break;
			}
			case Token::Type::KEYWORD: {
					std::string keyword = (*token++).content();

					if ( keyword == "assert" ) {
						process_assert(token);
					}
					else if ( keyword == "breakpoint" ) {
						mOwner->providePrinter()->print("hit breakpoint   [" + mOwner->filename() + ": " + Tools::toString(token->position().line) + "]");
					}
					else if ( keyword == "for" ) {
						process_for(token);
					}
					else if ( keyword == "if" ) {
						process_if(token);
					}
					else if ( keyword == "new" ) {
						Object n = process_new(token);
						returnValue.assign(n);
						return returnValue;
					}
					else if ( keyword == "print" ) {
						process_print(token);
					}
					else if ( keyword == "return" ) {
						returnValue.assign(parseExpression(token));
						return returnValue;
					}
					else if ( keyword == "switch" ) {
						process_switch(token);
					}
					else if ( keyword == "while" ) {
						process_while(token);
					}
				break;
			}
			case Token::Type::LITERAL: {
				parseExpression(token);
			} break;
			case Token::Type::PROTOTYPE:
			case Token::Type::TYPE: {
				handleType(token);
				break;
			}
			default: {
				mOwner->providePrinter()->print("invalid token '" + token->content() + "' as type " + Token::Type::convert(token->type()) + " found!");
				break;
			}
		}

		// switch to next token
		token++;
	}

	//pop_stack();
	return returnValue;
}

// syntax:
// assert(<condition>);
void Method::process_assert(TokenIterator& token)
{
	// find next open parenthesis
	TokenIterator condBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN, Token::Type::SEMICOLON);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin, 0, Token::Type::SEMICOLON);
	// find semicolon
	TokenIterator tmp = findNext(condEnd, Token::Type::SEMICOLON);

	Object condition = parseCondition(condBegin);

	if ( isFalse(condition) ) {
		throw AssertionFailed("'" + condition.value() + "'", token->position());
	}

	token = tmp;
}

// syntax:
// for ( int i = 0; i < 5; i += 1 ) {
// ...
// }
void Method::process_for(TokenIterator& token)
{
assert(!"not implemented");

	TokenIterator tmp = token;



	token = tmp;
}

// syntax:
// if ( <expression> ) {
// ...
// }
// else if ( <expression> ) {
// ...
// }
// else {
// ...
// }
void Method::process_if(TokenIterator& token)
{
	// find next open parenthesis
	TokenIterator condBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);
	// find next open curly bracket '{'
	TokenIterator bodyBegin = findNext(condEnd, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(++bodyBegin);

/*	
 * if-command only works if there is also an else-block
 * this is bad
 *
	// find next keyword if there is any
	TokenIterator elseToken = findNext(bodyEnd, Token::Type::KEYWORD);
	// else-begin
	TokenIterator elseBegin;
	// else-end
	TokenIterator elseEnd;

	// check if our next keyword is an else-keyword
	if ( elseToken != mTokens.end() && elseToken->content() == "else" ) {
		// we found an else keyword after our if-body
		// find next open curly bracket '{'
		elseBegin = findNext(elseToken, Token::Type::BRACKET_CURLY_OPEN);
		// find next balanced '{' & '}' pair
		elseEnd = findNextBalancedCurlyBracket(++elseBegin);
		// reset our end token
		bodyEnd = elseEnd;
	}
*/
	if ( isTrue(parseCondition(condBegin)) ) {
		process(bodyBegin, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);
//		bodyEnd = elseEnd;
	}
/*
	else {
		process(elseBegin, elseEnd, Token::Type::BRACKET_CURLY_CLOSE);
		token = elseBegin;
	}
*/

	token = bodyEnd;
}

// syntax:
// type method(<parameter list>);
Object Method::process_method(TokenIterator& token)
{
	TokenIterator tmp = token;

	std::string method = token->content();

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	VariablesList params;
	//ObjectList params;

	tmp = opened;
	// loop through all parameters seperated by colons
	while ( tmp != closed ) {
		Object v = parseExpression(tmp);
		params.push_back(v);

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

	return mOwner->execute(method, params, this);
}

// syntax:
// new <Object>([<parameter list>]);
Object Method::process_new(TokenIterator& token)
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

	VariablesList params;

	tmp = opened;
	// loop through all parameters seperated by colons
	while ( tmp != closed ) {
		Object v = parseExpression(tmp);
		params.push_back(v);

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

	Object object;
	if ( isPrototype ) {
		object = mRepository->createInstanceFromPrototype(prototype, type, name);
	}
	else {
		object = mRepository->createInstance(type, name);
	}

	object.connectPrinter(mOwner->providePrinter());
	object.connectRepository(mRepository);
	object.Constructor(params);

	return object;
}

// syntax:
// print(<expression>);
void Method::process_print(TokenIterator& token)
{
	// find open parenthesis
	TokenIterator opened = findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find closed parenthesis
	TokenIterator closed = findNextBalancedParenthesis(++opened);
	// find semicolon
	TokenIterator tmp = findNext(closed, Token::Type::SEMICOLON);

	Object v = parseExpression(opened);
	mOwner->providePrinter()->print(v.value() + "   [" + mOwner->filename() + ":" + Tools::toString(token->position().line) + "]");

	token = tmp;
}

// syntax:
// switch ( <expression> ) {
//		case <identifier>:
//			...
//		break;
// }
void Method::process_switch(TokenIterator& token)
{
assert(!"not implemented");

	TokenIterator tmp = token;



	token = tmp;
}

// syntax:
// while ( <condition> ) {
// ...
// }
void Method::process_while(TokenIterator& token)
{
	// find next open parenthesis
	TokenIterator condBegin = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);
	// find next open curly bracket '{'
	TokenIterator bodyBegin = findNext(condEnd, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(++bodyBegin);

	TokenIterator tmp = condBegin;

	while ( isTrue(parseCondition(tmp)) ) {
		process(bodyBegin, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// reset iterator
		tmp = condBegin;
	}

	token = bodyEnd;
}

const VariablesList& Method::provideSignature() const
{
	return mSignature;
}

void Method::push_stack(const std::string& scope)
{
	std::string s;

	if ( !mStack.empty() ) {
		s = mStack.back() + ".";
	}

	s += scope;
	mStack.push_back(s);
}

std::string Method::scope(const std::string& name) const
{
	std::string result;

	if ( !mStack.empty() ) {
		result = mStack.back();
		result += ".";
	}

	result += name;
	return result;
}

void Method::setOwner(Object *owner)
{
	mOwner = owner;
}

void Method::setRepository(Repository *repository)
{
	mRepository = repository;
}

void Method::setSignature(const VariablesList& params)
{
	mSignature = params;
}

void Method::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

Object Method::string_concat(const Object& v1, const Object& v2)
{
	return String(Tools::toString(v1.value() + v2.value()));
}


}
