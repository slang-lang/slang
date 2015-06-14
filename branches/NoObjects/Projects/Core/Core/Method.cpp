
// Header
#include "Method.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/BuildInObjects/Bool.h>
#include <Core/BuildInObjects/Number.h>
#include <Core/BuildInObjects/String.h>
#include <Core/Helpers/Math.h>
#include <Core/Helpers/Strings.h>
#include <Core/Interfaces/IPrinter.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Memory.h"
#include "Object.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Method::Method(IScope *parent, const std::string& name, const std::string& type)
: LocalScope(name, parent),
  Variable(name, type),
  mOwner(0),
  mRepository(0)
{
}

Method::~Method()
{
}

bool Method::operator() (const Method& first, const Method& second) const
{
	if ( first.name() == second.name() ) {
		ParameterList firstList = first.provideSignature();
		ParameterList secondList = second.provideSignature();

		// unable to identify return value during method call
		//if ( this->type() != other.type() ) {
		//	return this->type() < other.type();
		//}

		if ( firstList.size() == secondList.size() ) {
			ParameterList::const_iterator fIt = firstList.begin();
			ParameterList::const_iterator sIt = secondList.begin();

			for ( ; fIt != firstList.end() && sIt != secondList.end(); ++fIt, ++sIt ) {
				if ( fIt->type() != sIt->type() ) {
					return fIt->type() < sIt->type();
				}
			}
		}

		return firstList.size() < secondList.size();
	}

	return first.name() < second.name();
}

bool Method::operator< (const Method& other) const
{
	if ( this->name() == other.name() ) {
		ParameterList firstList = this->provideSignature();
		ParameterList secondList = other.provideSignature();

		// unable to identify return value during method call
		//if ( this->type() != other.type() ) {
		//	return this->type() < other.type();
		//}

		if ( firstList.size() == secondList.size() ) {
			ParameterList::const_iterator fIt = firstList.begin();
			ParameterList::const_iterator sIt = secondList.begin();

			for ( ; fIt != firstList.end() && sIt != secondList.end(); ++fIt, ++sIt ) {
				if ( fIt->type() != sIt->type() ) {
					return fIt->type() < sIt->type();
				}
			}
		}

		return firstList.size() < secondList.size();
	}

	return this->name() < other.name();
}

void Method::operator= (const Method& other)
{
	setConst(other.isConst());
	setStatic(other.isStatic());
	setLanguageFeatureState(other.languageFeatureState());

	// unregister current members
	for ( MemberCollection::const_iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ) {
		mRepository->removeReference(it->second);
		it = mLocalSymbols.erase(it);
	}

	// register new members
	for ( MemberCollection::const_iterator it = other.mLocalSymbols.begin(); it != other.mLocalSymbols.end(); ++it ) {
		addIdentifier(it->second);
		mRepository->addReference(it->second);
	}

	mOwner = other.mOwner;
	mParameter = other.mParameter;
	mRepository = other.mRepository;
	mTokens = other.mTokens;

	setSignature(other.provideSignature());
	visibility(other.visibility());
}

void Method::addIdentifier(Object *object)
{
	if ( !object ) {
		// ups..
		return;
	}

	if ( mLocalSymbols.find(object->name()) != mLocalSymbols.end() ) {
		if ( object->isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw Utils::DuplicateIdentiferException(object->name());
	}

	mLocalSymbols[object->name()] = object;
}

Object Method::execute(const ParameterList& params)
{
	if ( !isSignatureValid(params) ) {
		throw Utils::ParameterCountMissmatch("number or type of parameters incorrect");
	}

	switch ( languageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + name() + "' is marked as deprecated!"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + name() + "' is marked as not implemented!"); throw Utils::NotImplemented(name()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + name() + "'!"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + name() + "' is marked as unstable!"); break;
	}

	// add parameters as pseudo members
	ParameterList::const_iterator paramIt = params.begin();
	for ( ParameterList::const_iterator sigIt = mSignature.begin(); sigIt != mSignature.end(); ++sigIt ) {
		// initialize param with default value
		Parameter param(sigIt->name(), sigIt->type(), sigIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access(), sigIt->reference());

		if ( paramIt != params.end() ) {
			// override param with correct values
			param = Parameter(sigIt->name(), sigIt->type(), paramIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access(), paramIt->reference());
			// next iteration
			paramIt++;
		}

		switch ( param.access() ) {
			case Parameter::AccessMode::Unspecified: {
				throw Utils::Exception("access mode unspecified");
			} break;
			case Parameter::AccessMode::ByReference: {
				throw Utils::NotImplemented("handing over parameters as reference is not yet implemented");

/*
				Object *object = mMemory->getObject(param.reference());

				mRepository->addReference(object);
				addIdentifier(object);
*/
			} break;
			case Parameter::AccessMode::ByValue: {
				Object *object = mRepository->createInstance(param.type(), param.name());
				object->value(param.value());
				object->setConst(param.isConst());
				addIdentifier(object);
			} break;
		}
	}

	Object returnValue(name(), type());
	returnValue.connectRepository(mRepository);
	returnValue.visibility(visibility());

	TokenIterator start = mTokens.begin();
	process(&returnValue, start, mTokens.end());

	// after we gathered our result
	// let the garbage collector do it's magic
	garbageCollector();

	return returnValue;
}

void Method::garbageCollector(bool force)
{
	for ( MemberCollection::iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ) {
		if ( it->second->isStatic() && !force ) {
			it++;
			continue;
		}
		else {
			mRepository->removeReference(it->second);
			it = mLocalSymbols.erase(it);
		}
	}
}

Object* Method::getOwner() const
{
	return mOwner;
}

Object* Method::getSymbol(const std::string& token)
{
	std::string member, parent;
	Tools::split(token, parent, member);

	// either it is a local symbol...
	for ( MemberCollection::iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ++it ) {
		if ( it->first == token ) {
			return it->second;
		}
/*
		if ( !it->second->isValid() ) {
			continue;
		}
*/
		if ( it->second->name() == parent ) {
			return it->second->getMember(member);
		}
	}

	// ... or a member of our owner, if we have one
	if ( mOwner ) {
		return mOwner->getMember(token);
	}

	// ups.. this symbol is neiter a local symbol, nor a member
	throw Utils::UnknownIdentifer("identifier '" + token + "' not found!");
}

bool Method::isLocalSymbol(const std::string& token)
{
	std::string member, parent;
	Tools::split(token, parent, member);

	// check if token is a local variable
	// OR
	// loop through all locals and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ++it ) {
		if ( it->first == parent ) {
			return true;
		}
	}

	return false;
}

bool Method::isMember(const std::string& token)
{
	if ( !mOwner ) {
		return false;
	}

	// check if token is a member variable
	return mOwner->hasMember(token);
}

bool Method::isMethod(const std::string& token)
{
	if ( !mOwner ) {
		return false;
	}

	std::string member, parent;
	Tools::split(token, parent, member);

	// loop through all local symbols and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ++it ) {
		Object *object = it->second;
		if ( object && object->name() == parent ) {
			// check for member function
			if ( object->hasMethod(member) ) {
				return true;
			}
		}
	}

	if ( mOwner->hasMember(parent) ) {
		Object *obj = mOwner->getMember(parent);
		if ( obj ) {
			return obj->hasMethod(member);
		}
	}

	// check if token is a method of our parent object
	return mOwner->hasMethod(token);
}

bool Method::isMethod(const std::string& token, const ParameterList& params)
{
	if ( !mOwner ) {
		return false;
	}

	// check if token is a method of our parent object
	return mOwner->hasMethod(token, params);
}

bool Method::isSignatureValid(const ParameterList& params) const
{
	// check method signature by:
	// 1) comparing the number of parameters
	//	  by expecting the same number of parameters or less, we can make use of default parameters
	if ( mSignature.size() < params.size() ) {
		// we received more parameters than we expected
		return false;
	}

	// 2) by comparing each parameter one by one
	ParameterList::const_iterator paramIt = params.begin();
	ParameterList::const_iterator sigIt = mSignature.begin();

	while ( sigIt != mSignature.end() ) {
		if ( paramIt != params.end() ) {
			if ( /*(sigIt->access() != paramIt->access()) ||*/
				 /*(sigIt->isConst() != paramIt->isConst()) ||*/
				 (sigIt->type() != paramIt->type()) ) {
				return false;
			}
			paramIt++;
		}
		else {
			if ( !sigIt->hasDefaultValue() ) {
				return false;
			}
		}

		sigIt++;
	}

	// no differences found
	return true;
}

bool Method::parseCondition(TokenIterator& token)
{
	Object v1;
	parseExpression(&v1, token);

	for ( ; ; ) {
		Token::Type::E op = token->type();
		if ( op != Token::Type::COMPARE_EQUAL &&
			 op != Token::Type::COMPARE_GREATER &&
			 op != Token::Type::COMPARE_GREATER_EQUAL &&
			 op != Token::Type::COMPARE_LESS &&
			 op != Token::Type::COMPARE_LESS_EQUAL ) {
			return isTrue(v1);
		}

		// consume operator token
		token++;

		Object v2;
		parseExpression(&v2, token);

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

	return false;
}

void Method::parseExpression(Object *result, TokenIterator& start)
{
	parseFactors(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_ADD &&
			 op != Token::Type::MATH_SUBTRACT &&
			 op != Token::Type::STRING_ADD ) {
			return;
		}

		// consume operator token
		start++;

		Object v2;
		parseFactors(&v2, start);

		if ( op == Token::Type::MATH_ADD ) {
			*result = Math::add(*result, v2);
		}
		else if ( op == Token::Type::MATH_SUBTRACT ) {
			*result = Math::subtract(*result, v2);
		}
		else if ( op == Token::Type::STRING_ADD ) {
			*result = Strings::concat(*result, v2);
		}
	}
}

void Method::parseFactors(Object *result, TokenIterator& start)
{
	if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
		start++;
		parseExpression(result, start);

		if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
			throw Utils::SyntaxError("')' expected but "  + start->content() + " found", start->position());
		}

		start++;
	}
	else {
		parseTerm(result, start);
	}

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_MULTI &&
			 op != Token::Type::MATH_DIV ) {
			return;
		}

		// consume operator token
		start++;

		Object v2;
		if ( (start)->type() == Token::Type::PARENTHESIS_OPEN) {
			start++;
			parseExpression(&v2, start);

			if ( start->type() != Token::Type::PARENTHESIS_CLOSE ) {
				throw Utils::SyntaxError("')' expected but "  + start->content() + " found", start->position());
			}

			start++;
		}
		else {
			parseTerm(&v2, start);
		}

		if ( op == Token::Type::MATH_MULTI ) {
			*result = Math::multiply(*result, v2);
		}
		else {
			*result = Math::divide(*result, v2);
		}
	}
}

void Method::parseTerm(Object *result, TokenIterator& start)
{
	switch ( start->type() ) {
		case Token::Type::BOOLEAN: {
			*result = Bool(start->content());
		} break;
		case Token::Type::CONSTANT: {
			*result = Number(start->content());
		} break;
		case Token::Type::IDENTIFER: {
			// find out if we have to execute a method
			// or simply get a stored variable
			Object *symbol = getSymbol(start->content());
			if ( symbol ) {
				*result = *symbol;
			}
			else {
				if ( isMethod(start->content()) ) {
					*result = process_method(start);
				}
				else {
					throw Utils::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
				}
			}
		} break;
		case Token::Type::KEYWORD: {
			process(result, start, mTokens.end(), Token::Type::SEMICOLON);
		} break;
		case Token::Type::LITERAL: {
			*result = String(start->content());
		} break;
		default: {
			throw Utils::SyntaxError("identifier, literal or number expected but " + start->content() + " as " + Token::Type::convert(start->type()) + " found", start->position());
		} break;
	}

	start++;
}

void Method::process(Object *result, TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	// loop through all keywords and redirect to the corresponding method
	while ( token != end && token->type() != terminator && token->type() != Token::Type::ENDOFFILE ) {
		// decide what we want to do according to the type of token we have
		switch ( token->type() ) {
			case Token::Type::BOOLEAN:
			case Token::Type::CONSTANT:
			case Token::Type::LITERAL:
				parseExpression(result, token);
				break;
			case Token::Type::IDENTIFER:
				process_assign(token);
				break;
			case Token::Type::KEYWORD:
				if ( token->content() == "new" ) {
					*result = *process_new(token);
				}
				else if ( token->content() == "return" ) {
					parseExpression(result, ++token);
				}
				else {
					process_keyword(token);
				}
				break;
			case Token::Type::PROTOTYPE:
			case Token::Type::TYPE:
				process_type(token);
				break;
			default:
				throw Utils::SyntaxError("invalid token '" + token->content() + "' as type " + Token::Type::convert(token->type()) + " found", token->position());
				break;
		}

		token++;	// consume token
	}
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

	if ( !parseCondition(condBegin) ) {
		throw Utils::AssertionFailed("", token->position());
	}

	token = tmp;
}

void Method::process_assign(TokenIterator& token)
{
	// try to find assignment token
	TokenIterator assign = findNext(token, Token::Type::ASSIGN, Token::Type::SEMICOLON);
	// find next semicolon
	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Object result;
	if ( assign == token ) {
		// we don't have an assignment but a method call
		parseExpression(&result, token);

		token = end;
		return;
	}

	std::string identifier = token->content();

	Object *s = getSymbol(identifier);
	if ( !s ) {
		throw Utils::UnknownIdentifer("identified '" + identifier + "' not found", token->position());
	}
	if ( s->isConst() ) {
		throw Utils::ConstCorrectnessViolated("not allowed to modify const member '" + identifier + "'", token->position());
	}
	if ( this->isConst() && isMember(identifier) ) {
		throw Utils::ConstCorrectnessViolated("not allowed to modify member '" + identifier + "' in const method '" + this->name() + "'", token->position());
	}

	parseExpression(s, ++assign);

	if ( s->isFinal() && s->isModifiable() ) {
		// we have modified a final entity for the first time, we now have to set it so const 
		s->setConst(true);
		s->setFinal(false);
	}

	// assign == end should now be true
	token = end;
}

// syntax:
// delete <identifier>;
void Method::process_delete(TokenIterator& token)
{
	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Object *object = getSymbol(token->content());
	if ( object ) {
		mRepository->removeReference(object);
	}

	token = end;
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
	Object result;
	process(&result, decl, cond, Token::Type::SEMICOLON);

	while ( parseCondition(cond = conditionStart) ) {
		TokenIterator bb = begin;

		// process loop body
		process(&result, bb, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// execute loop expression
		expr = expressionStart;
		process(&result, expr, exprEnd, Token::Type::PARENTHESIS_CLOSE);
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

	Object result;
	if ( parseCondition(condBegin) ) {
		process(&result, bodyBegin, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

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
		process(&result, elseBegin, elseEnd, Token::Type::BRACKET_CURLY_CLOSE);

		// check if we executed all tokens
		if ( elseBegin != elseEnd ) {
			throw Utils::Exception("half evaluated else found!", bodyBegin->position());
		}

		token = elseEnd;
	}
	else {
		token = bodyEnd;
	}
}

void Method::process_keyword(TokenIterator& token)
{
	std::string keyword = (*token++).content();

	if ( keyword == "assert" ) {
		process_assert(token);
	}
	else if ( keyword == "delete" ) {
		process_delete(token);
	}
	else if ( keyword == "for" ) {
		process_for(token);
	}
	else if ( keyword == "if" ) {
		process_if(token);
	}
	else if ( keyword == "print" ) {
		process_print(token);
	}
	else if ( keyword == "switch" ) {
		process_switch(token);
	}
	else if ( keyword == "while" ) {
		process_while(token);
	}
// Debug only - begin
	else if ( keyword == "breakpoint" ) {
		mOwner->providePrinter()->print("hit breakpoint   [" + mOwner->Filename() + ": " + Tools::toString(token->position().line) + "]");
	}
// Debug only - end
}

// syntax:
// type method(<parameter list>);
Object Method::process_method(TokenIterator& token)
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
		Object object;
		parseExpression(&object, tmp);
		params.push_back(Parameter(object.name(), object.Typename(), object.value(), false, object.isConst(), Parameter::AccessMode::ByValue));

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

	Object *symbol = getSymbol(parent);
	if ( symbol ) {
		Object object;
		symbol->execute(&object, member, params, this);
		return object;
	}

	if ( isMethod(method) ) {
		Object object;
		mOwner->execute(&object, method, params, this);
		return object;
	}

	throw Utils::UnknownIdentifer("unknown/unexpected identifier '" + method + "' found", tmp->position());
}

// syntax:
// new <Object>([<parameter list>]);
Object* Method::process_new(TokenIterator& token)
{
	TokenIterator tmp = token++;

	std::string name = "<temporary object>";
	std::string prototype;

	if ( token->type() == Token::Type::PROTOTYPE ) {
		prototype = token->content();
		token++;
	}

	std::string type = token->content();

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	ParameterList params;

	tmp = opened;
	// loop through all parameters seperated by colons
	while ( tmp != closed ) {
		Object object;
		parseExpression(&object, tmp);
		params.push_back(Parameter(object.name(), object.Typename(), object.value(), false, object.isConst(), Parameter::AccessMode::ByValue));

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
	object->connectPrinter(mOwner->providePrinter());
	object->connectRepository(mRepository);
	object->Constructor(params);

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

	Object object;
	parseExpression(&object, opened);

	//mOwner->providePrinter()->print(object.value() + "   [" + mOwner->Filename() + ":" + Tools::toString(token->position().line) + "]");
	mOwner->providePrinter()->print(object.value());

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

void Method::process_type(TokenIterator& token)
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
		throw Utils::SyntaxError("identifier expected but '" + token->content() + "' found", token->position());
	}

	token++;

	std::string tmpStr = token->content();
	if ( tmpStr == "const" || tmpStr == "static" ) {
		token++;

		if ( tmpStr == "const" ) { isConst = true; }
		else if ( tmpStr == "final" ) { isFinal = true; }
		else if ( tmpStr == "static" ) { isStatic = true; }
	}

	TokenIterator assign = mTokens.end();
	if ( token->type() == Token::Type::ASSIGN ) {
		assign = ++token;
	}

	Object *object = getSymbol(name);
	if ( !object ) {
		object = mRepository->createInstance(type, name, prototype);

		if ( isConst ) object->setConst(true);
		if ( isFinal ) object->setFinal(true);
		if ( isStatic ) object->setStatic(true);

		if ( assign != mTokens.end() ) {
			//*object = parseExpression(assign);
			//token = assign;

			TokenIterator end = findNext(assign, Token::Type::SEMICOLON);
			parseExpression(object, assign);
			token = end;
		}

		addIdentifier(object);

		if ( token->type() != Token::Type::SEMICOLON ) {
			throw Utils::SyntaxError("';' expected but '" + token->content() + "' found", token->position());
		}
	}
	else {
		if ( !object->isStatic() ) {
			// upsi, did not clean up..
			throw Utils::DuplicateIdentiferException(name);
		}

		token = findNext(token, Token::Type::SEMICOLON);
	}
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

	Object result;
	while ( parseCondition(tmp) ) {
		TokenIterator bb = bodyBegin;

		process(&result, bb, bodyEnd, Token::Type::BRACKET_CURLY_CLOSE);

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


}
