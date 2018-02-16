
// Header
#include "Interpreter.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Defines.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/Stack.h>
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


#define DEBUGGER(exp) \
	if ( mDebugger ) { \
		mDebugger->exp; \
	}


Interpreter::Interpreter(Common::ThreadId threadId)
: mControlFlow(ControlFlow::Normal),
  mOwner(0),
  mThreadId(threadId)
{
	// initialize virtual machine stuff
	mDebugger = Core::Debugger::Instance().useDebugger() ? &Core::Debugger::Instance() : 0;
	mMemory = Controller::Instance().memory();
	mRepository = Controller::Instance().repository();
	mStack = Controller::Instance().stack();

	(void)mThreadId;
}

Interpreter::~Interpreter()
{
}

/*
 * collects all parameter objects between ( and )
 */
void Interpreter::collectParameterList(TokenIterator& token, ParameterList& params, std::list<Object>& objectList)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);

	TokenIterator opened = token;
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	token = closed;

	TokenIterator tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		objectList.push_back(Object());

		Object* obj = &objectList.back();
		try {
			expression(obj, tmp);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

/*
		// hack to prevent anonymous references to run out of scope, this will most likely produce memory leaks!!!
		if ( obj.getName() == ANONYMOUS_OBJECT ) {
			mMemory->add(obj.getReference());
		}
*/

		params.push_back(Parameter::CreateRuntime(obj->QualifiedOuterface(), obj->getValue(), obj->getReference()));

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COMMA);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		++tmp;
	}

	expect(Token::Type::PARENTHESIS_CLOSE, token);
}

/*
 * collects all tokens of a given scope (excluding the surrounding curly brackets)
 */
void Interpreter::collectScopeTokens(TokenIterator& token, TokenList& tokens)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(token, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	++token;			// don't collect {-token

	while ( token != bodyEnd ) {
		tokens.push_back((*token++));
	}

	token = bodyEnd;	// don't collect }-token

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
}

void Interpreter::deinitialize()
{
	// unwind stack
	mStack->pop();
}

/*
 * processes tokens and updates the given result
 */
ControlFlow::E Interpreter::execute(Common::Method* method, const ParameterList& params, Object* result)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method pointer provided!");
	}
	if ( method->isAbstract() ) {
		throw Common::Exceptions::AbstractException("cannot execute abstract method '" + method->getFullScopeName() + "'");
	}

	switch ( method->getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + method->getFullScopeName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + method->getFullScopeName() + "' is marked as not implemented"); throw Common::Exceptions::NotImplemented(method->getFullScopeName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unspecified: OSerror("unknown language feature state set for method '" + method->getFullScopeName() + "'"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + method->getFullScopeName() + "' is marked as unstable"); break;
	}

	Common::Method scope(*method);

	IScope* previousOwner = mOwner;
	mOwner = method->getEnclosingScope();

	initialize(&scope, method->getTokens(), method->mergeParameters(params));

	// notify debugger
	DEBUGGER( notifyEnter(&scope, Core::Debugger::immediateBreakToken) );
	// interpret scope tokens
	mControlFlow = interpret(getTokens(), result);

	// process & update control flow
	switch ( mControlFlow ) {
		case ControlFlow::Break:
		case ControlFlow::Continue:
		case ControlFlow::Normal:
			// verify method return reason
			if ( method->QualifiedTypename() != _void && result->QualifiedOuterface() != _void ) {
				throw Common::Exceptions::Exception("unnatural method return at '" + method->getFullScopeName() + "'");
			}

			// correct behavior detected, override control flow with normal state
			mControlFlow = ControlFlow::Normal;
			break;
		case ControlFlow::Return:
			// correct behavior detected, override control flow with normal state
			mControlFlow = ControlFlow::Normal;
			break;
		case ControlFlow::ExitProgram:
		case ControlFlow::Throw:
			// an ObjectiveScript exception has been thrown or we want to terminate
			break;
	}

	if ( mControlFlow == ControlFlow::Normal ) {
		switch ( method->getMethodType() ) {
			case MethodAttributes::MethodType::Constructor:
				dynamic_cast<Object*>(mOwner)->setConstructed(true);
				break;
			case MethodAttributes::MethodType::Destructor:
				dynamic_cast<Object*>(mOwner)->setConstructed(false);
				break;
			default:
				break;
		}
	}

	// notify debugger
	DEBUGGER( notifyExit(getScope(), Core::Debugger::immediateBreakToken) );

	deinitialize();

	mOwner = previousOwner;

	return mControlFlow;
}

void Interpreter::expression(Object* result, TokenIterator& start, bool completeEval)
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

		bool lvalue = isTrue(*result);

		// incomplete boolean evaluation (available for && and !& and || operators)
		if ( !completeEval ) {
			if ( op == Token::Type::AND && !lvalue) {
				*result = BoolObject(false);
				return;
			}
			else if ( op == Token::Type::NAND && !lvalue ) {
				*result = BoolObject(true);
				return;
			}
			else if ( op == Token::Type::NOR && lvalue ) {
				*result = BoolObject(false);
				return;
			}
			else if ( op == Token::Type::OR && lvalue ) {
				*result = BoolObject(true);
				return;
			}
		}

		++start;	// consume operator token

		Object rvalue;
		parseCondition(&rvalue, start);

		if ( op == Token::Type::AND ) {
			*result = BoolObject(lvalue && isTrue(rvalue));
		}
		else if ( op == Token::Type::NAND ) {
			*result = BoolObject(!lvalue || !isTrue(rvalue));
		}
		else if ( op == Token::Type::NOR ) {
			*result = BoolObject(!lvalue && !isTrue(rvalue));
		}
		else if ( op == Token::Type::OR ) {
			*result = BoolObject(lvalue || isTrue(rvalue));
		}
	}
}

NamedScope* Interpreter::getEnclosingMethodScope(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::NamedScope ) {
			return dynamic_cast<NamedScope*>(parent);
		}

		scope = parent;
	}

	return 0;
}

Common::Namespace* Interpreter::getEnclosingNamespace(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Common::Namespace* result = dynamic_cast<Common::Namespace*>(parent);
			if ( result ) {
				return result;
			}
		}

		scope = parent;
	}

	return 0;
}

Runtime::Object* Interpreter::getEnclosingObject(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Object* result = dynamic_cast<Object*>(parent);
			if ( result ) {
				return result;
			}
		}

		scope = parent;
	}

	return 0;
}

IScope* Interpreter::getScope() const
{
	return mStack->current()->getScope();
}

const TokenList& Interpreter::getTokens() const
{
	return mStack->current()->getTokens();
}

inline Symbol* Interpreter::identify(TokenIterator& token) const
{
	Symbol *result = 0;
	bool onlyCurrentScope = false;
	std::string prev_identifier;	// hack to allow special 'this'-handling

	while ( token->type() == Token::Type::IDENTIFIER || token->type() == Token::Type::TYPE ) {
		std::string identifier = token->content();

		if ( !result ) {
			result = getScope()->resolve(identifier, onlyCurrentScope, Visibility::Private);

			prev_identifier = identifier;

			if ( !result ) {
				Common::Namespace* space = getEnclosingNamespace(getScope());
				if ( space ) {
					result = getScope()->resolve(space->QualifiedTypename() + "." + identifier, onlyCurrentScope, Visibility::Private);
				}
			}
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::BluePrintObjectSymbol:
					result = dynamic_cast<Designtime::BluePrintObject*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = dynamic_cast<Common::Namespace*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::ObjectSymbol:
					result = dynamic_cast<Object*>(result)->resolve(identifier, onlyCurrentScope,
																	(prev_identifier == IDENTIFIER_THIS) ? Visibility::Private : Visibility::Public);
					break;
				case Symbol::IType::MethodSymbol:
					throw Common::Exceptions::NotSupported("cannot directly access locales of method");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		++token;

		TokenIterator tmp = token;
		++tmp;
		if ( tmp->type() != Token::Type::IDENTIFIER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		++token;
	}

	return result;
}

Symbol* Interpreter::identifyMethod(TokenIterator& token, const ParameterList& params) const
{
	Symbol *result = 0;
	bool onlyCurrentScope = false;
	std::string prev_identifier;	// hack to allow special 'this'-handling

	while ( token->type() == Token::Type::IDENTIFIER || token->type() == Token::Type::TYPE ) {
		std::string identifier = token->content();

		if ( !result ) {
			result = getScope()->resolve(identifier, onlyCurrentScope, Visibility::Private);

			prev_identifier = identifier;

			// look for an overloaded method
			if ( result && result->getSymbolType() == Symbol::IType::MethodSymbol ) {
				result = dynamic_cast<MethodScope*>(mOwner)->resolveMethod(identifier, params, onlyCurrentScope, Visibility::Private);
			}
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::BluePrintObjectSymbol:
					result = dynamic_cast<Designtime::BluePrintObject*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = dynamic_cast<Common::Namespace*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::ObjectSymbol:
					result = dynamic_cast<Object*>(result)->resolveMethod(identifier, params, true,
																		  (prev_identifier == IDENTIFIER_THIS) ? Visibility::Private : Visibility::Public);
					break;
				case Symbol::IType::MethodSymbol:
					throw Common::Exceptions::NotSupported("cannot directly access locales of method");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		++token;

		TokenIterator tmp = token;
		++tmp;
		if ( tmp->type() != Token::Type::IDENTIFIER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		++token;
	}

	return result;
}

void Interpreter::initialize(IScope* scope, const TokenList& tokens, const ParameterList& params)
{
	// add parameters as locale variables
	for ( ParameterList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		Object *object = 0;

		switch ( it->access() ) {
			case AccessMode::ByReference: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				if ( it->reference().isValid() ) {
					object->assign(*mMemory->get(it->reference()));
				}

				object->setMutability(it->mutability());

				scope->define(it->name(), object);
			} break;
			case AccessMode::ByValue: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				if ( it->reference().isValid() ) {
					throw Common::Exceptions::NotSupported("by value calls not allowed for objects", tokens.begin()->position());
				}

				object->setMutability(it->mutability());
				object->setValue(it->value());

				scope->define(it->name(), object);
			} break;
			case AccessMode::Unspecified: {
				throw Common::Exceptions::AccessMode("unspecified access mode");
			} break;
		}
	}

	// record stack
	mStack->push(scope, tokens, params);
}

/*
 * executes the given tokens in a separate scope
 */
ControlFlow::E Interpreter::interpret(const TokenList& tokens, Object* result, bool allowBreakAndContinue)
{
	// reset control flow to normal
	mControlFlow = ControlFlow::Normal;

	pushScope(0, allowBreakAndContinue);
		pushTokens(tokens);
			TokenIterator start = getTokens().begin();
			TokenIterator end = getTokens().end();

			process(result, start, end);
		popTokens();
	popScope();

	return mControlFlow;
}

AccessMode::E Interpreter::parseAccessMode(TokenIterator &token, bool isAtomicType)
{
	AccessMode::E result = isAtomicType ? AccessMode::ByValue : AccessMode::ByReference;

	if ( token->type() == Token::Type::RESERVED_WORD ) {
		result = AccessMode::convert(token->content());

		if ( result == AccessMode::Unspecified ) {
			// invalid type
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	return result;
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

		++start;	// consume comparator token

		Object rvalue;
		parseExpression(&rvalue, start);

		switch ( op ) {
			case Token::Type::COMPARE_EQUAL:
				*result = BoolObject(operator_binary_equal(result, &rvalue));
				break;
			case Token::Type::COMPARE_GREATER:
				*result = BoolObject(operator_binary_greater(result, &rvalue));
				break;
			case Token::Type::COMPARE_GREATER_EQUAL:
				*result = BoolObject(operator_binary_greater_equal(result, &rvalue));
				break;
			case Token::Type::COMPARE_LESS:
				*result = BoolObject(operator_binary_less(result, &rvalue));
				break;
			case Token::Type::COMPARE_LESS_EQUAL:
				*result = BoolObject(operator_binary_less_equal(result, &rvalue));
				break;
			case Token::Type::COMPARE_UNEQUAL:
				*result = BoolObject(!operator_binary_equal(result, &rvalue));
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

		++start;	// consume operator token

		Object rvalue;
		parseFactors(&rvalue, start);

		switch ( op ) {
			case Token::Type::BITAND:
				operator_binary_bitand(result, &rvalue);
				break;
			case Token::Type::BITCOMPLEMENT:
				operator_binary_bitcomplement(result, &rvalue);
				break;
			case Token::Type::BITOR:
				operator_binary_bitor(result, &rvalue);
				break;
			case Token::Type::MATH_ADDITION:
				operator_binary_plus(result, &rvalue);
				break;
			case Token::Type::MATH_SUBTRACT:
				operator_binary_subtract(result, &rvalue);
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

		++start;	// consume operator token

		Object rvalue;
		parseInfixPostfix(&rvalue, start);

		switch ( op ) {
			case Token::Type::MATH_DIVIDE:
				operator_binary_divide(result, &rvalue);
				break;
			case Token::Type::MATH_MODULO:
				operator_binary_modulo(result, &rvalue);
				break;
			case Token::Type::MATH_MULTIPLY:
				operator_binary_multiply(result, &rvalue);
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
		case Token::Type::MATH_ADDITION: {
			++start;
			parseExpression(result, start);
			// ignore infix addition operator
		} break;
		case Token::Type::MATH_SUBTRACT: {
			++start;
			parseExpression(result, start);
			operator_unary_minus(result);
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			++start;
			parseExpression(result, start);
			operator_unary_decrement(result);
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			++start;
			parseExpression(result, start);
			operator_unary_increment(result);
		} break;
		case Token::Type::OPERATOR_NOT: {
			++start;
			parseExpression(result, start);
			operator_unary_not(result);
		} break;
		case Token::Type::PARENTHESIS_OPEN: {
			++start;	// consume operator token

			expression(result, start);

			expect(Token::Type::PARENTHESIS_CLOSE, start);

			++start;	// consume operator token
		} break;
		default: {
			parseTerm(result, start);
		} break;
	}

	op = start->type();

	// postfix
	switch ( op ) {
		case Token::Type::BRACKET_OPEN: {
			throw Common::Exceptions::NotSupported("postfix [] operator not supported", start->position());
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			operator_unary_decrement(result);
			++start;
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			operator_unary_increment(result);
			++start;
		} break;
		case Token::Type::OPERATOR_IS: {
			++start;

			Symbol* symbol = identify(start);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("unkown identifier '" + start->content() + "' found", start->position());
			}

			++start;

			std::string compareType;

			if ( symbol->getSymbolType() == Symbol::IType::ObjectSymbol ) {
				compareType = static_cast<Object*>(symbol)->QualifiedTypename();
			}
			else if ( symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
				PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(start);

				compareType = dynamic_cast<Designtime::BluePrintObject*>(symbol)->QualifiedTypename();
				compareType = Designtime::Parser::buildRuntimeConstraintTypename(compareType, constraints);
			}
			else {
				throw Common::Exceptions::SyntaxError("invalid symbol type found", start->position());
			}

			*result = BoolObject(operator_binary_is(result, compareType));
		} break;
		case Token::Type::OPERATOR_NOT: {
			throw Common::Exceptions::NotSupported("postfix ! operator not supported", start->position());
/*
			operator_unary_validate(result);
			++start;
*/
		} break;
		default: {
		} break;
	}
}

Mutability::E Interpreter::parseMutability(TokenIterator& token)
{
	Mutability::E result = Mutability::Modify;

	if ( token->type() == Token::Type::MODIFIER ) {
		result = Mutability::convert(token->content());

		if ( result != Mutability::Const && result != Mutability::Modify ) {
			// local variables are only allowed to by modifiable or constant
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	return result;
}

void Interpreter::parseTerm(Object *result, TokenIterator& start)
{
	switch ( start->type() ) {
		case Token::Type::CONST_BOOLEAN: {
			BoolObject tmp(Utils::Tools::stringToBool(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_DOUBLE: {
			DoubleObject tmp(Utils::Tools::stringToDouble(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_FLOAT: {
			FloatObject tmp(Utils::Tools::stringToFloat(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_INTEGER: {
			IntegerObject tmp(Utils::Tools::stringToInt(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_LITERAL: {
			StringObject tmp(start->content());
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::IDENTIFIER:
		case Token::Type::TYPE: {
			// find out if we have to execute a method or simply get a stored variable

			TokenIterator tmpToken = start;
			Symbol *symbol = identify(start);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}

			switch ( symbol->getSymbolType() ) {
				case Symbol::IType::BluePrintObjectSymbol: {
					++start;

					PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(start);

					std::string newType = dynamic_cast<Designtime::BluePrintObject*>(symbol)->QualifiedTypename();
					newType = Designtime::Parser::buildRuntimeConstraintTypename(newType, constraints);

					Object tmp;
					try {
						expression(&tmp, start);
					}
					catch ( ControlFlow::E &e ) {
						mControlFlow = e;
						return;
					}

					typecast(&tmp, newType);

					operator_binary_assign(result, &tmp);
				} break;
				case Symbol::IType::MethodSymbol:
					process_method(tmpToken, result);
					start = tmpToken;
					++start;
					break;
				case Symbol::IType::NamespaceSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol resolved", start->position());
				case Symbol::IType::ObjectSymbol:
					operator_binary_assign(result, static_cast<Object*>(symbol));
					++start;
					break;
			}
		} break;
		case Token::Type::KEYWORD: {
			process_keyword(start, result);
			++start;
		} break;
		case Token::Type::SEMICOLON: {
		} break;
		default: {
			throw Common::Exceptions::SyntaxError("identifier, literal or constant expected but '" + start->content() + "' found", start->position());
		} break;
	}
}

void Interpreter::popScope()
{
	mStack->current()->popScope();
}

void Interpreter::popTokens()
{
	mStack->current()->popTokens();
}

/*
 * loop through all tokens and redirect to the corresponding method
 */
void Interpreter::process(Object *result, TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	TokenIterator localEnd = getTokens().end();

	while ( ( (token != localEnd) && (token != end) ) &&
			( (token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE) ) ) {

		if ( mControlFlow != ControlFlow::Normal ) {
			break;		// control flow has been broken, time to stop processing
		}

#ifdef USE_PROCESS_STATEMENT

		process_statement(token, result);

#else

		DEBUGGER( notify(getScope(), (*token)) );		// notify debugger

		switch ( token->type() ) {
			case Token::Type::IDENTIFIER:
			case Token::Type::TYPE:
				process_identifier(token, result);
				break;
			case Token::Type::KEYWORD:
				process_keyword(token, result);
				break;
			case Token::Type::BRACKET_CURLY_OPEN:
				process_scope(token, result);	// this opens a new scope
				break;
			case Token::Type::SEMICOLON:
				//++token;
				break;
			default:
				throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;	// consume token

#endif
	}
}

/*
 * syntax:
 * assert( <expression> );
 */
void Interpreter::process_assert(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

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

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	expect(Token::Type::SEMICOLON, token);
	//++token;
}

/*
 * syntax:
 * break;
 */
void Interpreter::process_break(TokenIterator& token)
{
	if ( !mStack->current()->allowBreakAndContinue() ) {
		OSwarn("break not allowed in " + token->position().toString());
		return;
	}

	mControlFlow = ControlFlow::Break;

	expect(Token::Type::SEMICOLON, token);
	//++token;
}

/*
 * syntax:
 * continue;
 */
void Interpreter::process_continue(TokenIterator& token)
{
	if ( !mStack->current()->allowBreakAndContinue() ) {
		OSwarn("continue not allowed in " + token->position().toString());
		return;
	}

	mControlFlow = ControlFlow::Continue;

	expect(Token::Type::SEMICOLON, token);
	//++token;
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

	Runtime::Object* source = dynamic_cast<Runtime::Object*>(symbol);
	if ( !source ) {
		throw Common::Exceptions::Exception("nullptr access!");
	}
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
			Object* object = static_cast<Object*>(symbol);

			object->assign(Object());
		} break;
		case Symbol::IType::BluePrintObjectSymbol:
		case Symbol::IType::MethodSymbol:
		case Symbol::IType::NamespaceSymbol:
			throw Common::Exceptions::TypeMismatch("member or local variable expected but symbol '" + symbol->getName() + "' found", token->position());
	}

	token = end;

	expect(Token::Type::SEMICOLON, token);
	//++token;
}

/*
 * syntax:
 * exit;
 */
void Interpreter::process_exit(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Object* data = mRepository->createInstance(IntegerObject::TYPENAME, ANONYMOUS_OBJECT, PrototypeConstraints());
	try {
		expression(data, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	mStack->exception() = ExceptionData(data, token->position());

	throw ControlFlow::ExitProgram;

	//expect(Token::Type::PARENTHESIS_CLOSE, token);
	//++token;
}

/*
 * syntax:
 * for ( <initialization>; <condition>; <expression> ) { ... }
 */
void Interpreter::process_for(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	TokenIterator initializationBegin = token;
	const TokenIterator conditionBegin = ++findNext(initializationBegin, Token::Type::SEMICOLON);
	const TokenIterator expressionBegin = ++findNext(conditionBegin, Token::Type::SEMICOLON);
	TokenIterator expressionEnd = findNext(expressionBegin, Token::Type::PARENTHESIS_CLOSE);

	bool hasCondition = (std::distance(conditionBegin, expressionBegin) > 1);
	bool hasExpression = (std::distance(expressionBegin, expressionEnd) > 1);
	bool hasInitialization = (std::distance(initializationBegin, conditionBegin) > 1);

	// process our declaration part
	// {
	if ( hasInitialization ) {
		Object declarationTmp;
		process(&declarationTmp, initializationBegin, conditionBegin);
	}
	// }

	expect(Token::Type::PARENTHESIS_CLOSE, expressionEnd);
	++expressionEnd;

	token = expressionEnd;

	// useCompound defines if a seperate scope block or a single statement has to be executed
	bool useCompound = (token->type() == Token::Type::BRACKET_CURLY_OPEN);
	TokenList loopTokens;

	if ( useCompound ) {
		collectScopeTokens(token, loopTokens);
	}

	for ( ; ; ) {
		// Condition parsing
		// {
		TokenIterator condBegin = conditionBegin;

		if ( hasCondition ) {
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
		if ( useCompound ) {
			// use previously collected tokens
			interpret(loopTokens, result, true);
		}
		else {
			// interpret a single statement only
			token = expressionEnd;

			process_statement(token, result);
		}

		switch ( mControlFlow ) {
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
		if ( hasExpression ) {
			TokenIterator exprBegin = expressionBegin;

			Object expressionTmp;
			process(&expressionTmp, exprBegin, expressionEnd, Token::Type::PARENTHESIS_CLOSE);
		}
		// }
	}
}

/*
 * syntax:
 * for ( <type definition> <identifier> : <instance> ) { ... }
 */
void Interpreter::process_foreach(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	TokenIterator typedefIt = token;

	// identify the loop variable's type
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + typedefIt->content() + "' not found", token->position());
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", token->position());
	}

	// create and define loop variable
	Object* loop = process_type(token, symbol, Initialization::NotAllowed);

	expect(Token::Type::COLON, token);
	++token;
	expect(Token::Type::IDENTIFIER, token);

	// identify collection symbol
	Object* collection = dynamic_cast<Object*>(identify(token));
	if ( !collection ) {
		throw Common::Exceptions::SyntaxError("invalid symbol '" + token->content() + "' found", token->position());
	}
	if ( !collection->isValid() ) {
		throw Runtime::Exceptions::NullPointerException("null pointer access", token->position());
	}
	if ( !collection->isInstanceOf("IIterateable") ) {
		throw Common::Exceptions::SyntaxError("symbol '" + collection->getName() + "' is not derived from IIteratable", token->position());
	}
	++token;

	// get collection's forward iterator
	Object iterator;
	collection->execute(&iterator, "getIterator", ParameterList());

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	// useCompound defines if a separate scope block or a single statement has to be processed
	bool hasCompound = (token->type() == Token::Type::BRACKET_CURLY_OPEN);
	TokenList loopTokens;
	const TokenIterator statementBegin = token;

	if ( hasCompound ) {
		collectScopeTokens(token, loopTokens);
	}

	for ( ; ; ) {
		// Setup
		// {
		Object tmp;
		iterator.execute(&tmp, "hasNext", ParameterList());	// evaluate hasNext method

		if ( !isTrue(tmp) ) {	// do we have more items to iterate over?
			break;
		}

		iterator.execute(loop, "next", ParameterList());	// get current item
		// }

		// Body parsing
		// {
		if ( hasCompound ) {
			// use previously collected tokens
			interpret(loopTokens, result, true);
		}
		else {
			// interpret a single statement only
			token = statementBegin;

			process_statement(token, result);
		}

		switch ( mControlFlow ) {
			case ControlFlow::Break: mControlFlow = ControlFlow::Normal; return;
			case ControlFlow::Continue: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::ExitProgram: mControlFlow = ControlFlow::ExitProgram; return;
			case ControlFlow::Normal: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::Return: mControlFlow = ControlFlow::Return; return;
			case ControlFlow::Throw: mControlFlow = ControlFlow::Throw; return;
		}
		// }
	}
}

/*
 * executes a method, processes an assign statement and instantiates new types
 */
void Interpreter::process_identifier(TokenIterator& token, Object* /*result*/)
{
	TokenIterator tmpToken = token;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + token->content() + "' not found", token->position());
	}

	try {
		if ( symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
			process_type(token, symbol, Initialization::Allowed);
		}
		else if ( symbol->getSymbolType() == Symbol::IType::MethodSymbol ) {
			token = tmpToken;	// reset token after call to identify

			Object tmpObject;
			process_method(token, &tmpObject);
		}
		else if ( symbol->getSymbolType() == Symbol::IType::ObjectSymbol ) {
			Object* object = dynamic_cast<Object*>(symbol);
			if ( object->isConst() ) {	// we tried to modify a const symbol (i.e. member, parameter or constant local variable)
				throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + object->getName() + "'", token->position());
			}

			++token;

			if ( token->category() == Token::Category::Assignment ) {
				TokenIterator assignToken = token;

				Object tmp;
				expression(&tmp, ++token);

				switch ( assignToken->type() ) {
					case Token::Type::ASSIGN: operator_binary_assign(object, &tmp); break;
					case Token::Type::ASSIGN_ADDITION: operator_binary_plus(object, &tmp); break;
					case Token::Type::ASSIGN_BITAND: operator_binary_bitand(object, &tmp); break;
					case Token::Type::ASSIGN_BITCOMPLEMENT: operator_binary_bitcomplement(object, &tmp); break;
					case Token::Type::ASSIGN_BITOR: operator_binary_bitor(object, &tmp); break;
					case Token::Type::ASSIGN_DIVIDE: operator_binary_divide(object, &tmp); break;
					case Token::Type::ASSIGN_MODULO: operator_binary_modulo(object, &tmp); break;
					case Token::Type::ASSIGN_MULTIPLY: operator_binary_multiply(object, &tmp); break;
					case Token::Type::ASSIGN_SUBTRACT: operator_binary_subtract(object, &tmp); break;
					default: throw Common::Exceptions::NotSupported("unsupported assignment " + assignToken->content(), assignToken->position());
				}
			}
			else {
				// by evaluation a standalone expression we can process ++/-- operators
				expression(object, token);
			}
		}
		else {
			throw Common::Exceptions::Exception("invalid symbol type found!");
		}
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
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
	TokenIterator condEnd = ++findNextBalancedParenthesis(condBegin);

	expect(Token::Type::BRACKET_CURLY_OPEN, condEnd);

	TokenIterator localEnd = getTokens().end();

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

	++bodyBegin;		// don't collect scope token
	token = bodyEnd;	// no matter what, at least set our token to our if-block's end

	// collect all tokens for our if-block
	TokenList ifTokens;
	while ( bodyBegin != bodyEnd ) {
		ifTokens.push_back((*bodyBegin));
		++bodyBegin;
	}

	if ( bodyEnd != localEnd ) {
		++bodyEnd;
	}

	bool targetReached = true;	// initially don't collect else-block tokens
	TokenIterator elseBegin = localEnd;
	TokenIterator elseEnd = localEnd;

	// look for an else-token
	if ( bodyEnd != localEnd && (bodyEnd->type() == Token::Type::KEYWORD && bodyEnd->content() == KEYWORD_ELSE ) ) {
		elseBegin = findNext(bodyEnd, Token::Type::BRACKET_CURLY_OPEN);
		// find next balanced '{' & '}' pair
		elseEnd = findNextBalancedCurlyBracket(elseBegin, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

		for ( ; ; ) {
			// check if there is another if after our else-block
			TokenIterator tmpIf = elseEnd;
			++tmpIf;
			if ( tmpIf != localEnd && tmpIf->type() == Token::Type::KEYWORD && tmpIf->content() == KEYWORD_ELSE ) {
				// find next balanced '{' & '}' pair
				elseEnd = findNextBalancedCurlyBracket(tmpIf, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

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
		++elseBegin;
	}


    Object condition;
	try {
		expression(&condition, condBegin, false);
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
	else if ( keyword == KEYWORD_FOREACH ) {
		process_foreach(token, result);
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
	else if ( keyword == KEYWORD_TYPEID ) {
		process_typeid(token, result);
	}
	else if ( keyword == KEYWORD_VAR ) {
		process_var(token, result);
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

	token = findNext(token, Token::Type::PARENTHESIS_OPEN);

	ParameterList params;
	std::list<Object> objectListHack;
	collectParameterList(token, params, objectListHack);

	Symbol* symbol = identifyMethod(tmp, params);

	Common::Method* method = dynamic_cast<Common::Method*>(symbol);
	if ( !method) {
		throw Common::Exceptions::UnknownIdentifer("could not resolve identifier '" + tmp->content() + "' with parameters '" + toString(params) + "'", tmp->position());
	}

	// compare callee's constness with its parent's constness
	Object* calleeParent = dynamic_cast<Object*>(method->getEnclosingScope());
	if ( calleeParent && calleeParent->isConst() && !method->isConst() ) {
		// we want to call a modifiable method of a const object... neeeeey!
		throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed for const object '" + calleeParent->getFullScopeName() + "'", tmp->position());
	}

	// check caller's constness
	Common::Method* owner = dynamic_cast<Common::Method*>(getEnclosingMethodScope());
	if ( owner && owner->isConst() ) {
		if ( owner->getEnclosingScope() == method->getEnclosingScope() && !method->isConst() ) {
			// check target method's constness
			// this is a const method and we want to call a modifiable method... neeeeey!
			throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + getScope()->getFullScopeName() + "'", tmp->position());
		}
	}

	// static method check
	if ( owner && owner->isStatic() && !method->isStatic() ) {
		throw Common::Exceptions::StaticException("non-static method \"" + method->ToString() + "\" called from static method \"" + owner->ToString() + "\"", tmp->position());
	}

	ControlFlow::E controlflow;

	if ( method->isExtensionMethod() ) {
		controlflow = method->execute(params, result, (*tmp));
	}
	else {
		controlflow = execute(method, params, result);
	}

	switch ( controlflow ) {
		case ControlFlow::ExitProgram:
			mControlFlow = ControlFlow::ExitProgram;
			throw ControlFlow::ExitProgram;		// promote control flow
		case ControlFlow::Throw:
			mControlFlow = ControlFlow::Throw;
			throw ControlFlow::Throw;			// promote control flow
		default:
			mControlFlow = ControlFlow::Normal;
			break;
	}
}

/*
 * syntax:
 * new <Typename>([<parameter list>]);
 */
void Interpreter::process_new(TokenIterator& token, Object *result)
{
	TokenIterator start = token;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + start->content() + "'");
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::Exception("blueprint symbol expected!");
	}

	++token;

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(token);

	ParameterList params;
	std::list<Object> objectListHack;
	collectParameterList(token, params, objectListHack);

	// create initialized reference of new object
	*result = *mRepository->createReference(static_cast<Designtime::BluePrintObject*>(symbol), ANONYMOUS_OBJECT, constraints, Repository::InitilizationType::Final);

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

	::Utils::PrinterDriver::Instance()->print(text.getValue().toStdString(), token->position().mFile, token->position().mLine);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;
}

/*
 * syntax:
 * return [<expression>];
 */
void Interpreter::process_return(TokenIterator& token, Object* result)
{
	if ( token->type() != Token::Type::SEMICOLON ) {
		try {
			expression(result, token);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}
	}

	mControlFlow = ControlFlow::Return;

	expect(Token::Type::SEMICOLON, token);
	//++token;
}

// syntax:
// { <statement> }
void Interpreter::process_scope(TokenIterator& token, Object* result)
{
	TokenList scopeTokens;
	collectScopeTokens(token, scopeTokens);

	mControlFlow = interpret(scopeTokens, result);
}

/*
 * process a single statement
 */
void Interpreter::process_statement(TokenIterator& token, Object* result)
{
	DEBUGGER( notify(getScope(), (*token)) );		// notify debugger

	switch ( token->type() ) {
		case Token::Type::IDENTIFIER:
		case Token::Type::TYPE:
			process_identifier(token, result);
			break;
		case Token::Type::KEYWORD:
			process_keyword(token, result);
			break;
		case Token::Type::BRACKET_CURLY_OPEN:
			process_scope(token, result);	// this opens a new scope
			break;
		case Token::Type::SEMICOLON:
			++token;
			break;
		default:
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}
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
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = ++findNextBalancedParenthesis(condBegin);

	// evaluate switch-expression
	Object expr;
	try {
		expression(&expr, condBegin, false);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	expect(Token::Type::BRACKET_CURLY_OPEN, condEnd);

	TokenIterator localEnd = getTokens().end();

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

	++bodyBegin;	// don't collect scope token
	token = bodyEnd;

	// CaseBlock is our data holder object for each case-block, hence the name
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
	CaseBlock defaultBlock = CaseBlock(localEnd, localEnd);

	// collect all case-blocks for further processing
	while ( bodyBegin != bodyEnd ) {
		if ( bodyBegin->type() == Token::Type::KEYWORD && bodyBegin->content() == KEYWORD_CASE ) {
			TokenIterator tmp = findNextBalancedCurlyBracket(bodyBegin, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

			caseBlocks.push_back(CaseBlock(bodyBegin, tmp));

			bodyBegin = tmp;
		}
		else if ( bodyBegin->type() == Token::Type::KEYWORD && bodyBegin->content() == KEYWORD_DEFAULT ) {
			if ( defaultBlock.mBegin != localEnd ) {
				throw Common::Exceptions::SyntaxError("duplicate default entry for switch statement");
			}

			TokenIterator tmp = findNextBalancedCurlyBracket(bodyBegin, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

			defaultBlock = CaseBlock(bodyBegin, tmp);

			bodyBegin = tmp;
		}
		++bodyBegin;
	}

	bool caseMatched = false;

	// loop through all case-labels and match their expressions against the switch-expression
	for ( CaseBlocks::iterator it = caseBlocks.begin(); it != caseBlocks.end(); ++it ) {
		it->mBegin++;

		// evaluate switch-expression
		Object condition;
		try {
			expression(&condition, it->mBegin);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		// compare case block expression with switch-expression
		if ( operator_binary_equal(&expr, &condition) ) {
			caseMatched = true;

			expect(Token::Type::COLON, it->mBegin++);
			expect(Token::Type::BRACKET_CURLY_OPEN, it->mBegin++);	// don't collect scope token

			// collect case-block tokens
			TokenList caseTokens;
			while ( it->mBegin != it->mEnd ) {
				caseTokens.push_back((*it->mBegin));
				it->mBegin++;
			}

			// interpret case-block tokens
			mControlFlow = interpret(caseTokens, result, true);

			switch ( mControlFlow ) {
				case ControlFlow::Break:
					mControlFlow = ControlFlow::Normal;
					return;	// stop matching the remaining case-statements
				case ControlFlow::Continue:
					mControlFlow = ControlFlow::Normal;
					break;	// continue matching the remaining case-statements
				case ControlFlow::Normal:
					mControlFlow = ControlFlow::Normal;
					return;	// stop matching the remaining case-statements
				case ControlFlow::ExitProgram:
				case ControlFlow::Return:
				case ControlFlow::Throw:
					return;	// no further processing, keep current control flow state
			}
		}
	}

	// execute the default block (if present)
	if ( !caseMatched && defaultBlock.mBegin != localEnd ) {
		defaultBlock.mBegin++;
		expect(Token::Type::COLON, defaultBlock.mBegin++);

		TokenList defaultTokens;
		collectScopeTokens(defaultBlock.mBegin, defaultTokens);

		// interpret case-block tokens
		mControlFlow = interpret(defaultTokens, result, true);

		switch ( mControlFlow ) {
			case ControlFlow::Break:
			case ControlFlow::Continue:
			case ControlFlow::Normal:
				mControlFlow = ControlFlow::Normal;	// reset control flow state to normal
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
	// check if our parent scope is a method that is allowed to throw exceptions
	Common::Method* method = dynamic_cast<Common::Method*>(getEnclosingMethodScope());
	if ( method && !method->throws() ) {
		// this method is not marked as 'throwing', so we are not allowed to throw exceptions here
		OSwarn(std::string(method->getFullScopeName() + " throws although it is not marked with 'throws' in " + token->position().toString()).c_str());
	}

	// determine if we are about to rethrow an exception or throw a new one
	if ( token->type() != Token::Type::SEMICOLON ) {
		Object* data = mRepository->createInstance(_object, ANONYMOUS_OBJECT, PrototypeConstraints());
		try {
			expression(data, token);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		mStack->exception() = ExceptionData(data, token->position());
	}

	mControlFlow = ControlFlow::Throw;

	expect(Token::Type::SEMICOLON, token);
	//++token;

	// notify our debugger that an exception has been thrown
	DEBUGGER( notifyExceptionThrow(getScope(), (*token)) );
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

	TokenList tryTokens;
	collectScopeTokens(token, tryTokens);

	// process try-block
	mControlFlow = interpret(tryTokens, result);

	TokenIterator tmp = lookahead(token, 1);
	TokenIterator localEnd = getTokens().end();

	std::list<TokenIterator> catches;
	TokenIterator finallyToken = localEnd;

	// collect all catch- and finally-blocks
	for ( ; ; ) {
		if ( tmp != localEnd && tmp->content() == KEYWORD_CATCH ) {
			catches.push_back(tmp);

			tmp = findNextBalancedCurlyBracket(tmp, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

			if ( std::distance(token, tmp) ) {
				token = tmp;	// set exit token
			}
		}
		else if ( tmp != localEnd && tmp->content() == KEYWORD_FINALLY ) {
			if ( finallyToken != localEnd ) {
				throw Common::Exceptions::SyntaxError("multiple finally blocks are not allowed");
			}

			finallyToken = tmp;
			tmp = findNextBalancedCurlyBracket(tmp, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

			if ( std::distance(token, tmp) ) {
				token = tmp;	// set exit token
			}
		}
		else {
			break;	// reached end of try-catch-finally-block
		}

		++tmp;
	}

	// process catch-blocks (if present)
	if ( mControlFlow == ControlFlow::Throw ) {
		if ( catches.empty() ) {
			// reset control flow in case no catch-block has been defined
			mControlFlow = ControlFlow::Normal;
		}

		Object* exception = mStack->exception().getData();

		for ( std::list<TokenIterator>::const_iterator it = catches.begin(); it != catches.end(); ++it ) {
			TokenIterator catchIt = (*it);
			++catchIt;

			pushScope();	// push a new scope to allow reuse of the same exception instance name

			// parse exception type (if present)
			if ( catchIt->type() == Token::Type::PARENTHESIS_OPEN ) {
				++catchIt;

				Symbol* symbol = identify(catchIt);
				if ( !symbol ) {
					throw Common::Exceptions::UnknownIdentifer("identifier '" + catchIt->content() + "' not found", catchIt->position());
				}
				if ( symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
					throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", catchIt->position());
				}

				// create new exception type instance
				Object* type = process_type(catchIt, symbol, Initialization::NotAllowed);

				expect(Token::Type::PARENTHESIS_CLOSE, catchIt++);

				if ( !type || !exception ) {
					throw Common::Exceptions::Exception("could not create exception type instance", catchIt->position());
				}

				// compare given exception type with thrown type inheritance
				if ( !exception->isInstanceOf(type->QualifiedTypename()) ) {
					popScope();		// pop exception instance scope
					continue;
				}

				// exception type match with thrown type, start with the real exception handling
				operator_binary_assign(type, exception);
			}

			// notify our debugger that an exception has been caught
			DEBUGGER( notifyExceptionCatch(getScope(), (*catchIt)) );

			TokenList catchTokens;
			collectScopeTokens(catchIt, catchTokens);

			// reset control flow to allow correct exception handling
			mControlFlow = ControlFlow::Normal;

			// execute catch-block if an exception has been thrown
			mControlFlow = interpret(catchTokens, result);

/*
			if ( exception ) {
				getScope()->define(exception->getName(), exception);
			}
*/

			popScope();		// pop exception instance scope
			break;
		}
	}

	// store current control flow and reset it after finally block has been executed
	Runtime::ControlFlow::E tmpControlFlow = mControlFlow;

	// reset current control flow to allow execution of finally-block
	mControlFlow = Runtime::ControlFlow::Normal;

	// process finally-block (if present)
	if ( finallyToken != localEnd ) {
		++finallyToken;

		TokenList finallyTokens;
		collectScopeTokens(finallyToken, finallyTokens);

		// execute finally-block
		interpret(finallyTokens, result);
	}

	// reset control flow to previous state if not set differently by finally statement
	if ( mControlFlow == Runtime::ControlFlow::Normal && tmpControlFlow != Runtime::ControlFlow::Throw ) {
		mControlFlow = tmpControlFlow;
	}
}

/*
 * syntax:
 * <type> [ "<" <type> ">" ] <identifier> [const|modify] [ref|val] [= <initialization>]
 */
Object* Interpreter::process_type(TokenIterator& token, Symbol* symbol, Initialization::E initialization)
{
	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(++token);

	expect(Token::Type::IDENTIFIER, token);

	std::string name = (token++)->content();

	Mutability::E mutability = parseMutability(token);

	// not-atomic types are references by default
	AccessMode::E accessMode = parseAccessMode(token, static_cast<Designtime::BluePrintObject*>(symbol)->isAtomicType());

	Object* object = mRepository->createInstance(static_cast<Designtime::BluePrintObject*>(symbol), name, constraints);
	object->setConst(mutability == Mutability::Const);

	getScope()->define(name, object);


	if ( token->type() == Token::Type::ASSIGN ) {
		++token;

		if ( initialization != Initialization::Allowed ) {
			// type declaration without initialization has been requested
			throw Common::Exceptions::NotSupported("type initialization not allowed here", token->position());
		}

		// execute assignment statement
		try {
			Object tmp;
			expression(&tmp, token);

			if ( accessMode == AccessMode::ByReference && (tmp.isAtomicType() && !tmp.getReference().isValid()) ) {
				throw Runtime::Exceptions::InvalidAssignment("reference type expected", token->position());
			}
/* temporarily disabled because this prevents the usage of =operator with atomic types
			else if ( accessMode == AccessMode::ByValue && tmp.getReference().isValid() ) {
				throw Runtime::Exceptions::InvalidAssignment("value type expected", token->position());
			}
*/

			// this separate assignment operation ensures that are type system is not bypassed
			operator_binary_assign(object, &tmp, token->position());
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;

			return 0;
		}
	}
	else if ( initialization == Initialization::Required ) {
		// initialization is required (probably because type inference is used) but no initialization sequence found
		throw Common::Exceptions::NotSupported("type inference required initialization", token->position());
	}
	else if ( initialization >= Initialization::Allowed &&
			  accessMode == AccessMode::ByReference &&
			  static_cast<Designtime::BluePrintObject*>(symbol)->isAtomicType() ) {
		// atomic reference without initialization found
		throw Common::Exceptions::NotSupported("atomic references need to be initialized", token->position());
	}

	return object;
}

/*
 * syntax:
 * typeid ( <expression> );
 */
void Interpreter::process_typeid(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Runtime::Exceptions::InvalidSymbol("typeid(): invalid symbol provided", token->position());
	}

	switch ( symbol->getSymbolType() ) {
		case Symbol::IType::BluePrintObjectSymbol:
			*result = StringObject(static_cast<Designtime::BluePrintObject*>(symbol)->QualifiedTypename());
			break;
		case Symbol::IType::ObjectSymbol:
			*result = StringObject(static_cast<Object*>(symbol)->QualifiedTypename());
			break;
		default:
			throw Runtime::Exceptions::InvalidSymbol("typeid(): cannot resolve symbol type", token->position());
	}

	++token;
	expect(Token::Type::PARENTHESIS_CLOSE, token);
}

/*
 * syntax:
 * var <identifier> = <expression>;
 */
void Interpreter::process_var(TokenIterator& token, Object* /*result*/)
{
	expect(Token::Type::IDENTIFIER, token);

	std::string name = (token++)->content();

	Mutability::E mutability = parseMutability(token);

	expect(Token::Type::ASSIGN, token);
	++token;

	// execute assignment statement
	// {
	Object var;
	try {
		expression(&var, token);
	}
	catch ( ControlFlow::E &e ) {
		mControlFlow = e;

		return;
	}

	Object* object = mRepository->createInstance(var.QualifiedTypename(), name, PrototypeConstraints(), Repository::InitilizationType::Final);
	object->setConst(mutability == Mutability::Const);

	getScope()->define(name, object);

	operator_binary_assign(object, &var, token->position());
	// }

	expect(Token::Type::SEMICOLON, token);
	//++token;
}

/*
 * syntax:
 * while ( <condition> ) { ... }
 */
void Interpreter::process_while(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin)++;

	expect(Token::Type::PARENTHESIS_CLOSE, condEnd);
	++condEnd;

	// useCompound defines if a seperate scope block or a single statement has to be executed
	bool useCompound = (condEnd->type() == Token::Type::BRACKET_CURLY_OPEN);
	TokenList whileTokens;

	if ( useCompound ) {
		// find next open curly bracket '{'
		TokenIterator bodyBegin = condEnd;
		// find next balanced '{' & '}' pair
		TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		++bodyBegin;	// don't collect scope token;
		token = bodyEnd;

		while ( bodyBegin != bodyEnd ) {
			whileTokens.push_back((*bodyBegin));
			++bodyBegin;
		}
	}

	for ( ; ; ) {
		TokenIterator tmp = condBegin;

		Object condition;
		try {
			expression(&condition, tmp, false);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		if ( !isTrue(condition) ) {
			break;
		}

		if ( useCompound ) {
			// use previously collected tokens
			interpret(whileTokens, result, true);
		}
		else {
			// interpret a single statement only
			token = condEnd;

			process_statement(token, result);
		}

		switch ( mControlFlow ) {
			case ControlFlow::Break: mControlFlow = ControlFlow::Normal; return;
			case ControlFlow::Continue: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::ExitProgram: mControlFlow = ControlFlow::ExitProgram; return;
			case ControlFlow::Normal: mControlFlow = ControlFlow::Normal; break;
			case ControlFlow::Return: mControlFlow = ControlFlow::Return; return;
			case ControlFlow::Throw: mControlFlow = ControlFlow::Throw; return;
		}
	}
}

void Interpreter::pushScope(IScope* scope, bool allowBreakAndContinue)
{
	StackFrame* stack = mStack->current();

	bool allowDelete = !scope;

	if ( !scope ) {
		scope = new SymbolScope(stack->getScope());
	}

	stack->pushScope(scope, allowDelete, allowBreakAndContinue || stack->allowBreakAndContinue());
}

void Interpreter::pushTokens(const TokenList& tokens)
{
	mStack->current()->pushTokens(tokens);
}


}
}
