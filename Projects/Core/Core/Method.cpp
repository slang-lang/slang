
// Header
#include "Method.h"

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


Method::Method(IScope *parent, const std::string& name, const std::string& type)
: LocalScope(name, parent),
  MethodSymbol(name),
  Variable(name, type),
  mControlFlow(Interpreter::ControlFlow::None),
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
	if ( this != &other ) {
		setConst(other.isConst());
		setFinal(other.isFinal());
		setLanguageFeatureState(other.languageFeatureState());

		// unregister current members
		for ( MemberCollection::const_iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ) {
			mRepository->removeReference(it->second);
			it = mLocalSymbols.erase(it);
		}

		// register new members
		for ( MemberCollection::const_iterator it = other.mLocalSymbols.begin(); it != other.mLocalSymbols.end(); ++it ) {
			addIdentifier(it->first, it->second);
			mRepository->addReference(it->second);
		}

		mOwner = other.mOwner;
		mParameter = other.mParameter;
		mRepository = other.mRepository;
		mTokens = other.mTokens;

		setSignature(other.provideSignature());
		visibility(other.visibility());
	}
}

void Method::addIdentifier(const std::string& name, Object *object)
{
	if ( !object ) {
		// ups..
		return;
	}

	std::string insertName = name;
	if ( insertName.empty() ) {
		insertName = object->getName();
	}

	// define object in our scope (this will replace 'addIdentifier' in the distant future)
	define(insertName, object);

	if ( mLocalSymbols.find(insertName) != mLocalSymbols.end() ) {
		if ( object->isStatic() ) {
			// don't insert static members a second time
			// just return silently
			return;
		}

		throw Utils::Exceptions::DuplicateIdentifer("addIdentifier: " + insertName);
	}

	mLocalSymbols[insertName] = object;
}

void Method::execute(const ParameterList& params, Object *result)
{
	mControlFlow = Interpreter::ControlFlow::None;		// reset this every time we start executing a method

	if ( !isSignatureValid(params) ) {
		throw Utils::Exceptions::ParameterCountMissmatch("incorrect number or type of parameters");
	}

	switch ( languageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + name() + "' is marked as deprecated!"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + name() + "' is marked as not implemented!"); throw Utils::Exceptions::NotImplemented(name()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + name() + "'!"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + name() + "' is marked as unstable!"); break;
	}

	// add parameters as locale variables
	ParameterList::const_iterator paramIt = params.begin();
	for ( ParameterList::const_iterator sigIt = mSignature.begin(); sigIt != mSignature.end(); ++sigIt ) {
		// initialize param with default value
		Parameter param(sigIt->name(), sigIt->type(), sigIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access());

		if ( paramIt != params.end() ) {
			Parameter::AccessMode::E access = sigIt->access();

			// override param with correct value
			param = Parameter(sigIt->name(), sigIt->type(), paramIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), access, paramIt->pointer());
			// next iteration
			paramIt++;
		}

		switch ( param.access() ) {
			case Parameter::AccessMode::Unspecified: {
				throw Utils::Exceptions::AccessMode("unspecified");
			} break;
			case Parameter::AccessMode::ByReference: {
				Object *object = param.pointer();
				object->setConst(param.isConst());

				addIdentifier(param.name(), object);
			} break;
			case Parameter::AccessMode::ByValue: {
				Object *object = mRepository->createInstance(param.type(), param.name());
				object->setValue(param.value());	// in case we have a default value
				if ( param.pointer() ) {
					*object = Object(*param.pointer());
				}
				object->setConst(param.isConst());

				addIdentifier(param.name(), object);
			} break;
		}
	}

	result->connectRepository(mRepository);
	result->overrideType(type());
	result->visibility(visibility());


	// parse tokens in Method::process
	// {
	pushTokens(mTokens);
		TokenIterator start = getTokens().begin();
		TokenIterator end = getTokens().end();

		process(result, start, end);
	popTokens();
	// }

/*
	// parse tokens in Interpreter::process
	// {
	Interpreter interpreter(this, getName());
	interpreter.setRepository(mRepository);
	interpreter.setTokens(mTokens);

	interpreter.execute(result);
	// }
*/

	// let the garbage collector do it's magic after we gathered our result
	garbageCollector();
}

void Method::expression(Object *result, TokenIterator& start)
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

void Method::garbageCollector(bool force)
{
	for ( MemberCollection::iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ) {
		if ( it->second->isStatic() && !force ) {
			it++;
			continue;
		}
		else {
			undefine(it->first, it->second);

			mRepository->removeReference(it->second);
			it = mLocalSymbols.erase(it);
		}
	}
}

Object* Method::getOwner() const
{
	return mOwner;
}

const std::string& Method::getTypeName() const
{
	return mVarType;
}

bool Method::isMember(const std::string& token) const
{
	return (mOwner && mOwner->getMember(token));
}

Object* Method::getObject(const std::string& symbol) const
{
	std::string member, parent;
	Tools::split(symbol, parent, member);

	// either it is a local symbol...
	for ( MemberCollection::const_iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ++it ) {
		if ( it->first == symbol ) {
			return it->second;
		}

		if ( it->first == parent ) {
			return it->second->getMember(member);
		}
	}

	// ... or a member of our owner, if we have one
	if ( mOwner ) {
		return mOwner->getMember(symbol);
	}

	// ups.. this symbol is neither a local symbol, nor a member
	throw Utils::Exceptions::UnknownIdentifer("identifier '" + symbol + "' not found!");
}

const TokenList& Method::getTokens() const
{
	return mTokenStack.back();
}

bool Method::isMethod(const std::string& token) const
{
	if ( !mOwner ) {
		return false;
	}

	std::string method, parent;
	Tools::split(token, parent, method);

	// loop through all local symbols and ask them if this identifier belongs to them
	for ( MemberCollection::const_iterator it = mLocalSymbols.begin(); it != mLocalSymbols.end(); ++it ) {
		if ( !it->second ) {
			continue;
		}

		if ( it->first == parent ) {
			// check for member function
			if ( it->second->hasMethod(method) ) {
				return true;
			}
		}
	}

	Object *obj = mOwner->getMember(parent);
	if ( obj ) {
		return obj->hasMethod(method);
	}

	// check if token is a method of our parent object
	return mOwner->hasMethod(token);
}

bool Method::isMethod(const std::string& token, const ParameterList& params) const
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

void Method::parseCondition(Object *result, TokenIterator& start)
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

void Method::parseExpression(Object *result, TokenIterator& start)
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

void Method::parseFactors(Object *result, TokenIterator& start)
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

void Method::parseTerm(Object *result, TokenIterator& start)
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
			else {
				Object *object = getObject(start->content());
				if ( object ) {
					*result = *object;
				}
				else {
					if ( isMethod(start->content()) ) {
						process_method(start, result);
					}
					else {
						throw Utils::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
					}
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

void Method::popTokens()
{
	mTokenStack.pop_back();
}

void Method::process(Object *result, TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	// loop through all keywords and redirect to the corresponding method
	while ( ((token != getTokens().end()) && (token != end) ) &&
			((token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE)) ) {

		if ( mControlFlow != Interpreter::ControlFlow::None ) {
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
void Method::process_assert(TokenIterator& token)
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
void Method::process_break(TokenIterator& token)
{
	//System::Print(KEYWORD_BREAK, token->position());

(void)token;
	mControlFlow = Interpreter::ControlFlow::Break;
}

// syntax:
// continue;
void Method::process_continue(TokenIterator& token)
{
	//System::Print(KEYWORD_CONTINUE, token->position());

(void)token;
	mControlFlow = Interpreter::ControlFlow::Continue;
}

// syntax:
// delete <identifier>;
void Method::process_delete(TokenIterator& token)
{
	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Object *object = getObject(token->content());
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
		mControlFlow = Interpreter::ControlFlow::None;

		TokenIterator condBegin = conditionBegin;

		Object condition;
		expression(&condition, condBegin);

		if ( isFalse(condition) ) {
			break;
		}
		// }

		// Body parsing
		// {
		mControlFlow = Interpreter::ControlFlow::None;

		pushTokens(loopTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			VoidObject tmp;
			process(&tmp, tmpBegin, tmpEnd);
		}
		popTokens();

		if ( mControlFlow == Interpreter::ControlFlow::Break ) {
			break;
		}
		else if ( mControlFlow == Interpreter::ControlFlow::Continue ) {
			continue;
		}
		else if ( mControlFlow == Interpreter::ControlFlow::Return ) {
			return;
		}
		// }

		// Expression parsing
		// {
		mControlFlow = Interpreter::ControlFlow::None;

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
void Method::process_identifier(TokenIterator& token, Token::Type::E terminator)
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

	//Object *symbol = getObject(identifier);
	Object *symbol = static_cast<Object*>(resolve(identifier));
	if ( !symbol ) {
		throw Utils::Exceptions::UnknownIdentifer("identifier '" + identifier + "' not found", token->position());
	}
	if ( symbol->isConst() ) {
		throw Utils::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + identifier + "'", token->position());
	}
	if ( isMember(identifier) && (this->isConst() || mOwner->isConst()) ) {
		throw Utils::Exceptions::ConstCorrectnessViolated("tried to modify member '" + identifier + "' in const method '" + this->name() + "'", token->position());
	}

	expression(symbol, ++assign);

	if ( !symbol->isConst() && symbol->isFinal() ) {
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
void Method::process_if(TokenIterator& token)
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

			Object tmp;
			process(&tmp, tmpBegin, tmpEnd);
		}
		popTokens();
	}
	else if ( !elseTokens.empty() ) {
		pushTokens(elseTokens);
		{
			TokenIterator tmpBegin = getTokens().begin();
			TokenIterator tmpEnd = getTokens().end();

			Object tmp;
			process(&tmp, tmpBegin, tmpEnd);
		}
		popTokens();
	}
}

void Method::process_keyword(TokenIterator& token, Object *result)
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
void Method::process_method(TokenIterator& token, Object *result)
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

	std::string member, parent;
	Tools::split(method, parent, member);

	Object *object = getObject(parent);
	if ( object ) {
		object->execute(result, member, params, this);
		return;
	}

	if ( isMethod(method, params) ) {
		mOwner->execute(result, method, params, this);
		return;
	}

	throw Utils::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + method + "' found", tmp->position());
}

// syntax:
// new <Object>([<parameter list>]);
void Method::process_new(TokenIterator& token, Object *result)
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

	mRepository->removeReference(object);
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

	StringObject text;
	expression(&text, opened);

	System::Print(text.getValue(), token->position());

	token = tmp;
}

// syntax:
// return <expression>;
void Method::process_return(TokenIterator& token, Object *result)
{
	expression(result, token);

	mControlFlow = Interpreter::ControlFlow::Return;
}

// syntax:
// { <statement> }
void Method::process_scope(TokenIterator& token, Object *result)
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

	mControlFlow = scope.mControlFlow;
*/

	Interpreter interpreter(this, getName());
	interpreter.setRepository(mRepository);
	interpreter.setTokens(tmpTokens);

	mControlFlow = interpreter.execute(result);

	token = scopeEnd;
}

// syntax:
// switch ( <expression> ) {
//		case <identifier>:
//			...
//		break;
// }
void Method::process_switch(TokenIterator& token)
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

	//Object *object = getSymbol(name);
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

		addIdentifier(name, object);

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
void Method::process_while(TokenIterator& token)
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
		mControlFlow = Interpreter::ControlFlow::None;

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

		if ( mControlFlow == Interpreter::ControlFlow::Break ) {
			break;
		}
		else if ( mControlFlow == Interpreter::ControlFlow::Continue ) {
			continue;
		}
		else if ( mControlFlow == Interpreter::ControlFlow::Return ) {
			return;
		}
	}
}

const ParameterList& Method::provideSignature() const
{
	return mSignature;
}

void Method::pushTokens(const TokenList& tokens)
{
	mTokenStack.push_back(tokens);
}

Symbol* Method::resolve(const std::string& name, bool onlyCurrentScope) const
{
	std::string member, parent;
	Tools::split(name, parent, member);

	Symbol *result = LocalScope::resolve(parent, onlyCurrentScope);

	if ( name == parent ) {
		return result;
	}

	if ( result ) {
		switch ( result->getType() ) {
			case Symbol::IType::MemberSymbol:
			case Symbol::IType::ObjectSymbol:
				return static_cast<Object*>(result)->resolve(member);
			case Symbol::IType::AtomicTypeSymbol:
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::UnknownSymbol:
				break;
		}
	}

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

void Method::setSignature(const ParameterList& params)
{
	mSignature = params;
}

void Method::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}


}
