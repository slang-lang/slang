
// Header
#include "Method.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/BuildInObjects/Bool.h>
#include <Core/BuildInObjects/Number.h>
#include <Core/BuildInObjects/String.h>
#include <Core/Interfaces/IPrinter.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Memory.h"
#include "Object.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Method::Method(const std::string& name, const std::string& type)
: Variable(name, type),
  mMemory(0),
  mOwner(0),
  mRepository(0)
{
}

Method::~Method()
{
	garbageCollector();
}

/*
void Method::addIdentifier(Object object)
{
	if ( mLocales.find(object.name()) != mLocales.end() ) {
		if ( object.isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw DuplicateIdentifer(object.name());
	}

	mLocales[object.name()] = object;
}
*/

/*
void Method::addIdentifier(const Reference& r)
{
	Object *object = mMemory->getObject(r);

	if ( mLocales.find(object->name()) != mLocales.end() ) {
		if ( object->isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw DuplicateIdentifer(object->name());
	}

	mLocales[object->name()] = r;
}
*/

void Method::addIdentifier(Variable object)
{
	if ( mLocales.find(object.name()) != mLocales.end() ) {
		if ( object.isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw Utils::DuplicateIdentifer(object.name());
	}

	mLocales[object.name()] = object;
}

//Variable Method::execute(const VariablesList& params)
Variable Method::execute(const ParameterList& params)
{
	if ( !isSignatureValid(params) ) {
		throw Utils::ParameterCountMissmatch("number or type of parameters incorrect");
	}

	switch ( languageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + name() + "' is marked as deprecated!"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + name() + "' is marked as not implemented!"); throw Utils::NotImplemented(name()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so no need to log anything here */ break;
		case LanguageFeatureState::Unknown: /* ignore this one */ break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + name() + "' is marked as unstable!"); break;
	}

	ParameterList::const_iterator rIt = mSignature.begin();
	// add parameters as pseudo members
	for ( ParameterList::const_iterator it = params.begin(); it != params.end(); ++it, ++rIt ) {
		addIdentifier(Variable((*rIt).name(), (*it).type(), (*it).value()));

/*
		Reference ref = mMemory->newObject(new Object((*rIt).name(), "", (*it).type(), (*it).value()));

		addIdentifier(ref);
*/
	}

	Variable returnValue(name(), type(), "");
	returnValue.setVisibility(visibility());

	try {	// try to execute our method
		TokenIterator start = mTokens.begin();
		returnValue.value(process(start, mTokens.end()).value());
	}
	catch ( Utils::Exception &e ) {	// if any thing happens clean up the mess
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
	for ( MemberMap::iterator it = mLocales.begin(); it != mLocales.end(); ++it ) {
		if ( (*it).second.isStatic() ) {
			tmp.insert((*it));
			continue;			
		}

/*
		Variable *object = mMemory->getObject(it->second);

		if ( object && object->isStatic() ) {
			tmp.insert((*it));
			continue;
		}

		mMemory->deleteObject(it->second);
*/
	}

	mLocales.clear();
	mLocales = tmp;
}

const Reference& Method::getLocale(const std::string& name) const
{
	(void)name;
/*
	for ( MemberMap::const_iterator it = mLocales.begin(); it != mLocales.end(); ++it ) {
		if ( it->first == name ) {
			return it->second;
		}
	}
*/

	return mMemory->getNullReference();
}

Variable& Method::getVariable(const std::string& name)
{
	for ( MemberMap::iterator it = mLocales.begin(); it != mLocales.end(); ++it ) {
		if ( it->second.name() == name ) {
			return it->second;
		}

/*
		Object *object = mMemory->getObject(it->second);

		if ( object && object->name() == name ) {
			return *object;
		}
*/
	}

	Variable& o = mOwner->getMember(name);
	if ( o.name() != "" ) {
		return o;
	}

	throw Utils::SyntaxError("expected identifier but '" + name + "' found!");
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
		throw Utils::SyntaxError("identifier expected but '" + token->content() + "' found", token->position());
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

/*
	Reference ref;
	if ( isPrototype ) {
		ref = mRepository->createReferenceFromPrototype(prototype, type, name);
	}
	else {
		ref = mRepository->createReference(type, name);
	}


	Object *object = mMemory->getObject(ref);

	if ( isConst ) object->setConst(true);
	if ( isStatic ) object->setStatic(true);

	if ( assign != mTokens.end() ) {
		object->assign(parseExpression(assign));
		token = assign;
	}

	addIdentifier(ref);
*/

	Variable object;
	if ( isPrototype ) {
		object = mRepository->createInstanceFromPrototype(prototype, type, name);
	}
	else {
		object = mRepository->createInstance(type, name);
	}

	if ( isConst ) object.setConst(true);
	if ( isStatic ) object.setStatic(true);

	if ( assign != mTokens.end() ) {
		object.value(parseExpression(assign).value());
		token = assign;
	}

	addIdentifier(object);


	if ( token->type() != Token::Type::SEMICOLON ) {
		throw Utils::SyntaxError("';' expected but '" + token->content() + "' found", token->position());
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

bool Method::isFalse(const Variable& v) const
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
	for ( MemberMap::iterator it = mLocales.begin(); it != mLocales.end(); ++it ) {
		if ( it->first == token ) {
			return true;
		}

/*
		Object *object = mMemory->getObject(it->second);
		if ( object && object->name() == parent ) {
			// check for member variable
			if ( object->hasMember(member) ) {
				return true;
			}

			// check for member function
			if ( object->hasMethod(member) ) {
				return true;
			}
		}
*/
	}

	return false;
}

bool Method::isMember(const std::string& token)
{
	std::string member, parent;
	Tools::split(token, parent, member);

	// check if token is a local variable
	// OR
	// loop through all locals and ask them if this identifier belongs to them
	for ( MemberMap::iterator it = mLocales.begin(); it != mLocales.end(); ++it ) {
		if ( it->first == token ) {
			return true;
		}

/*
		Object *object = mMemory->getObject(it->second);
		if ( object && object->name() == parent ) {
			// check for member variable
			if ( object->hasMember(member) ) {
				return true;
			}
		}
*/
	}

	// check if token is a member variable
	return mOwner->hasMember(token);
}

bool Method::isMethod(const std::string& token)
{
	std::string member, parent;
	Tools::split(token, parent, member);

/*
	// loop through all locals and ask them if this identifier belongs to them
	for ( MemberMap::iterator it = mLocales.begin(); it != mLocales.end(); ++it ) {
		Object *object = mMemory->getObject(it->second);
		if ( object && object->name() == parent ) {
			// check for member function
			if ( object->hasMethod(member) ) {
				return true;
			}
		}
	}
*/

	if ( mOwner->hasMember(parent) ) {
		// TODO: our owning object has a member with this name, delegate this to him
	}

	// check if token is a method of our parent object
	return mOwner->hasMethod(token);
}

bool Method::isMethod(const std::string& token, const ParameterList& params)
{
	// check if token is a method of our parent object
	return mOwner->hasMethod(token, params);
}

//bool Method::isSignatureValid(const VariablesList& params) const
//{
//	// check method signature by:
//	// 1) comparing the number of parameters
//	if ( mSignature.size() != params.size() ) {
//		return false;
//	}
//
//	// 2) by comparing their types
//	VariablesList::const_iterator pIt = params.begin();
//	for ( VariablesList::const_iterator it = mSignature.begin(); it != mSignature.end(); ++it, ++pIt ) {
//		if ( (*it).type() != (*pIt).type() ) {
//			return false;
//		}
//	}
//
//	// no difference was found
//	return true;
//}

bool Method::isSignatureValid(const ParameterList& params) const
{
	// check method signature by:
	// 1) comparing the number of parameters
	if ( mSignature.size() != params.size() ) {
		return false;
	}

	// 2) by comparing their types
	ParameterList::const_iterator pIt = params.begin();
	for ( ParameterList::const_iterator it = mSignature.begin(); it != mSignature.end(); ++it, ++pIt ) {
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

bool Method::isTrue(const Variable& v) const
{
	// check value is false
	if ( v.value() == "0" || v.value() == "0.0" || v.value() == "false" ) {
		return false;
	}

	// value is not false, so return true
	return true;
}

Variable Method::math_add(const Variable& v1, const Variable& v2)
{
	Variable result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 + f2));
	}
	else {
		//throw Utils::TypeMismatch("for addition: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw Utils::TypeMismatch("for addition: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Variable Method::math_divide(const Variable& v1, const Variable& v2)
{
	Variable result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 / f2));
	}
	else {
		//throw Utils::TypeMismatch("for division: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw Utils::TypeMismatch("for division: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Variable Method::math_multiply(const Variable& v1, const Variable& v2)
{
	Variable result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 * f2));
	}
	else {
		//throw Utils::TypeMismatch("for multiplication: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw Utils::TypeMismatch("for multiplication: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Variable Method::math_subtract(const Variable& v1, const Variable& v2)
{
	Variable result;

	if ( v1.type() == "Number" && v2.type() == "Number" ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.value());
		float f2 = Tools::stringToFloat(v2.value());

		result = Number(Tools::toString(f1 - f2));
	}
	else {
		//throw Utils::TypeMismatch("for subtraction: " + v1.value() + " and/or " + v2.value() + " are not of type 'float'");
		throw Utils::TypeMismatch("for subtraction: '" + v1.value() + "' and/or '" + v2.value() + "' are not of type 'Number'");
	}

	return result;
}

Variable Method::parseAtom(TokenIterator& start)
{
	Variable v;

	switch ( start->type() ) {
		case Token::Type::BOOLEAN: {
			v = Bool(start->content());
		} break;
		case Token::Type::CONSTANT: {
			v = Number(start->content());
		} break;
		case Token::Type::IDENTIFER: {
			// find out if we have to execute a method
			// or simply get a stored variable
			if ( isLocal(start->content()) ) {
				v = getVariable(scope(start->content()));
			}
			if ( isMember(start->content()) ) {
				v = getVariable(start->content());
			}
			else if ( isMethod(start->content()) ) {
				v = process_method(start);
			}
			else {
				throw Utils::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}
		} break;
		case Token::Type::KEYWORD: {
			v = process(start, mTokens.end(), Token::Type::SEMICOLON);
		} break;
		case Token::Type::LITERAL: {
			v = String(start->content());
		} break;
		default:
			throw Utils::SyntaxError("identifier, literal or number expected but " + start->content() + " as " + Token::Type::convert(start->type()) + " found", start->position());
			break;
	}

	start++;
	return v;
}

Variable Method::parseCondition(TokenIterator& token)
{
	Variable v1;
	v1 = parseExpression(token);

	for ( ; ; ) {
		Token::Type::E op = token->type();
		if ( op != Token::Type::COMPARE_EQUAL && op != Token::Type::COMPARE_GREATER && op != Token::Type::COMPARE_GREATER_EQUAL &&
			op != Token::Type::COMPARE_LESS && op != Token::Type::COMPARE_LESS_EQUAL ) {
				return v1;
		}

		token++;
		Variable v2 = parseExpression(token);

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

	return Variable();
}

Variable Method::parseExpression(TokenIterator& start)
{
	Variable result;
	result = parseSummands(start);

	return result;
}

Variable Method::parseFactors(TokenIterator& start)
{
	Variable v1;
	if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
		v1 = parseExpression(++start);

		if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
			// ups...
		}
	}
	else {
		v1 = parseAtom(start);
	}

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_MULTI && op != Token::Type::MATH_DIV ) {
			return v1;
		}

		start++;
		Variable v2 = parseAtom(start);

		if ( op == Token::Type::MATH_MULTI ) {
			v1 = math_multiply(v1, v2);
		}
		else {
			v1 = math_divide(v1, v2);
		}
	}

	return Variable();
}

Variable Method::parseSummands(TokenIterator& start)
{
	Variable v1;
	if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
		v1 = parseExpression(++start);

		if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
			// ups...
		}
	}
	else {
		v1 = parseAtom(start);
	}

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_ADD && op != Token::Type::MATH_SUBTRACT &&
			 op != Token::Type::STRING_ADD ) {
			return v1;
		}

		start++;
		Variable v2 = parseFactors(start);

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

	return Variable();
}

void Method::pop_stack()
{
	mStack.pop_back();
}

Variable Method::process(TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	Variable returnValue;

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


				if ( isLocal(token->content()) ) {
					// ok
				}
				else if ( isMember(token->content()) ) {
					// ok
				}
				else {
					// not ok
					throw Utils::UnknownIdentifer(token->content(), token->position());
				}

				Variable& s = getVariable(token->content());
				Variable t = parseExpression(++assign);

				if ( s.isConst() || (this->isConst() && isMember(s.name())) ) {
					throw Utils::Exception("can not change const object!", token->position());
				}

				s.value(t.value());

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
						mOwner->providePrinter()->print("hit breakpoint   [" + mOwner->Filename() + ": " + Tools::toString(token->position().line) + "]");
					}
					else if ( keyword == "for" ) {
						process_for(token);
					}
					else if ( keyword == "if" ) {
						process_if(token);
					}
					else if ( keyword == "new" ) {
						Reference ref = process_new(token);
						returnValue = (*mMemory->getObject(ref));

						return returnValue;
					}
					else if ( keyword == "print" ) {
						process_print(token);
					}
					else if ( keyword == "return" ) {
						returnValue.value(parseExpression(token).value());
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

	Variable condition = parseCondition(condBegin);

	if ( isFalse(condition) ) {
		throw Utils::AssertionFailed("'" + condition.value() + "'", token->position());
	}

	token = tmp;
}

// syntax:
// for ( <expression>; <condition>; <expression> ) { }
// i.e. for ( int i = 0; i < 5; i += 1 ) {
// ...
// }
void Method::process_for(TokenIterator& token)
{
	// find declaration
	TokenIterator decl = ++findNext(token, Token::Type::PARENTHESIS_OPEN);
	// find condition
	TokenIterator cond = ++findNext(decl, Token::Type::SEMICOLON);
	const TokenIterator conditionStart = cond;
	// find expression
	TokenIterator expr = ++findNext(cond, Token::Type::SEMICOLON);
	const TokenIterator expressionStart = expr;
	// find next open curly bracket '{'
	const TokenIterator exprEnd = findNext(expr, Token::Type::PARENTHESIS_CLOSE);

	const TokenIterator bodyBegin = findNext(expr, Token::Type::BRACKET_CURLY_OPEN);
	// find next balanced '{' & '}' pair
	TokenIterator begin = bodyBegin;
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(++begin);

	// process our declaration part
	process(decl, cond, Token::Type::SEMICOLON);

	while ( isTrue(parseCondition(cond = conditionStart)) ) {
		TokenIterator bb = begin;

		// process loop body
		process(bb, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// execute loop expression
		expr = expressionStart;
		process(expr, exprEnd, Token::Type::PARENTHESIS_CLOSE);
	}

	token = bodyEnd;
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

	TokenIterator elseBegin = mTokens.end();
	TokenIterator elseEnd = mTokens.end();

	TokenIterator eb = bodyEnd;
	if ( ++eb != mTokens.end() ) {
		if ( eb->type() == Token::Type::KEYWORD && eb->content() == "else" ) {
			elseBegin = findNext(eb, Token::Type::BRACKET_CURLY_OPEN);
			// find next balanced '{' & '}' pair
			elseEnd = findNextBalancedCurlyBracket(++elseBegin);
		}
	}

	if ( isTrue(parseCondition(condBegin)) ) {
		process(bodyBegin, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// check if we executed all tokens
		if ( bodyBegin != bodyEnd ) {
			throw Utils::Exception("half evaluated if found!", bodyBegin->position());
		}

		if ( elseEnd != mTokens.end() ) {
			token = elseEnd;
		}
		else {
			token = bodyEnd;
		}
	}
	else if ( elseBegin != mTokens.end() ) {
		process(elseBegin, elseEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// check if we executed all tokens
		if ( elseBegin != elseEnd ) {
			throw Utils::Exception("half evaluated else found!", bodyBegin->position());
		}

		token = elseEnd;
	}
}

// syntax:
// type method(<parameter list>);
Variable Method::process_method(TokenIterator& token)
{
	TokenIterator tmp = token;

	std::string method = token->content();

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	ReferencesList paramsAsReferences;
	ParameterList params;

	tmp = opened;
	// loop through all parameters seperated by colons
	while ( tmp != closed ) {
		Variable v = parseExpression(tmp);
		params.push_back(Parameter(v.name(), v.type(), v.value(), Parameter::AccessMode::ByValue));

/*
		Reference r = mMemory->getAddress(&v);
		paramsAsReferences.push_back(r);
*/

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

//TODO: what if we want to execute a method of another object?!?!

	if ( mOwner->hasMethod(method, params) ) {
		return mOwner->execute(method, params, this);
	}

	throw Utils::UnknownIdentifer("unknown/unexpected identifier '" + method + "' found", tmp->position());
}

// syntax:
// new <Object>([<parameter list>]);
//Object Method::process_new(TokenIterator& token)
Reference Method::process_new(TokenIterator& token)
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
		Variable v = parseExpression(tmp);
		params.push_back(Parameter(v.name(), v.type(), v.value(), Parameter::AccessMode::ByValue));

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

	Reference ref;
	if ( isPrototype ) {
		ref = mRepository->createReferenceFromPrototype(prototype, type, name);
	}
	else {
		ref = mRepository->createReference(type, name);
	}

	Object *object = mMemory->getObject(ref);
	object->connectMemory(mMemory);
	object->connectPrinter(mOwner->providePrinter());
	object->connectRepository(mRepository);
	object->Constructor(params);

	return ref;

/*
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
*/
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

	Variable v = parseExpression(opened);
	mOwner->providePrinter()->print(v.value() + "   [" + mOwner->Filename() + ":" + Tools::toString(token->position().line) + "]");

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
		TokenIterator bb = bodyBegin;

		process(bb, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// reset iterator
		tmp = condBegin;
	}

	token = bodyEnd;
}

//const VariablesList& Method::provideSignature() const
const ParameterList& Method::provideSignature() const
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

void Method::setMemory(Memory *memory)
{
	mMemory = memory;
}

void Method::setOwner(Object *owner)
{
	mOwner = owner;
}

void Method::setRepository(Repository *repository)
{
	mRepository = repository;
}

void Method::setSignature(const ParameterList& params)
{
	mSignature = params;
}

void Method::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

Variable Method::string_concat(const Variable& v1, const Variable& v2)
{
	return String(Tools::toString(v1.value() + v2.value()));
}


}
