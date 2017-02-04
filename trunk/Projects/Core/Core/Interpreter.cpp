
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
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/Stack.h>
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Utils.h>
#include "Defines.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Interpreter::Interpreter()
: mControlFlow(ControlFlow::Normal),
  mOwner(0)
{
	// initialize virtual machine stuff
	mDebugger = &Core::Debugger::Instance();
	mMemory = Controller::Instance().memory();
	mRepository = Controller::Instance().repository();
	mStack = Controller::Instance().stack();
}

Interpreter::~Interpreter()
{
}

/*
 * processes tokens and updates the given result
 */
ControlFlow::E Interpreter::execute(Common::Method* method, const ParameterList& params, Object* result)
{
	if ( !mRepository ) {
		throw Common::Exceptions::Exception("mRepository not set");
	}

	if ( method->isAbstract() ) {
		throw Common::Exceptions::AbstractException("cannot execute abstract method '" + method->getFullScopeName() + "'");
	}

	switch ( method->getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + method->getFullScopeName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + method->getFullScopeName() + "' is marked as not implemented"); throw Common::Exceptions::NotImplemented(method->getFullScopeName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + method->getFullScopeName() + "'"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + method->getFullScopeName() + "' is marked as unstable"); break;
	}

	Common::Method scope(*method);

	IScope* previousOwner = mOwner;

	mOwner = method->getEnclosingScope();

	ParameterList executedParams = method->mergeParameters(params);

	// add parameters as locale variables
	for ( ParameterList::const_iterator it = executedParams.begin(); it != executedParams.end(); ++it ) {
		Object *object = 0;

		switch ( it->access() ) {
			case Parameter::AccessMode::ByReference: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				if ( it->reference().isValid() ) {
					object->assign(*mMemory->get(it->reference()));
				}

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);

				scope.define(it->name(), object);
			} break;
			case Parameter::AccessMode::ByValue: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				if ( it->reference().isValid() ) {
#ifdef ALLOW_BY_VALUE_COPY
					OSwarn("by value call for object in " + scope.ToString());

					object->copy(*mMemory->get(it->reference()));
#else
					throw Common::Exceptions::NotSupported("by value calls not allowed for objects", getTokens().begin()->position());
#endif
				}

				object->setValue(it->value());

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);

				scope.define(it->name(), object);
			} break;
			case Parameter::AccessMode::Unspecified: {
				throw Common::Exceptions::AccessMode("unspecified access mode");
			} break;
		}
	}

	// record stack
	mStack->push(&scope, executedParams);
	// notify debugger
	mDebugger->notifyEnter(&scope, Core::Debugger::immediateBreakToken);
	// interpret scope tokens
	mControlFlow = interpret(getTokens(), result);

	// process & update control flow
	switch ( mControlFlow ) {
		case ControlFlow::Break:
		case ControlFlow::Continue:
		case ControlFlow::Normal:
			// verify method return reason
			if ( method->QualifiedTypename() != VoidObject::TYPENAME && result->QualifiedOuterface() != VoidObject::TYPENAME ) {
				throw Common::Exceptions::Exception("unnatural method return at '" + method->getFullScopeName() + "'");
			}

			// correct behavior detected, override control flow with normal state
			mControlFlow = ControlFlow::Normal;
			break;
		case ControlFlow::Return:
			// validate return value

			if (result->QualifiedOuterface() == NULL_TYPE ) {
				// no type cast necessary for null objects
			}
			else if ( method->QualifiedTypename() != VoidObject::TYPENAME && result->QualifiedOuterface() != method->QualifiedTypename() ) {
#ifdef ALLOW_IMPLICIT_CASTS
				//OSwarn("implicit type conversion from " + result->QualifiedOuterface() + " to " + method->QualifiedTypename() + " in " + getTokens().begin()->position().toString());

				typecast(result, method->QualifiedTypename());
#else
				throw Runtime::Exceptions::ExplicitCastRequired("explicit cast required for type conversion from " + result->QualifiedOutterface() + " to " + method->QualifiedTypename() + " in " + method->getFullScopeName());
#endif
			}

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
	mDebugger->notifyExit(getScope(), Core::Debugger::immediateBreakToken);
	// unwind stack trace
	mStack->pop();

	mOwner = previousOwner;

	return mControlFlow;
}

void Interpreter::expression(Object* result, TokenIterator& start)
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

		++start;	// consume operator token

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

	while ( token->type() == Token::Type::IDENTIFER || token->type() == Token::Type::TYPE ) {
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
				case Symbol::IType::BluePrintEnumSymbol:
					result = dynamic_cast<Designtime::BluePrintEnum*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
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
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol found");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		++token;

		TokenIterator tmp = token;
		++tmp;
		if ( tmp->type() != Token::Type::IDENTIFER && tmp->type() != Token::Type::TYPE ) {
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

	while ( token->type() == Token::Type::IDENTIFER || token->type() == Token::Type::TYPE ) {
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
				case Symbol::IType::BluePrintEnumSymbol:
					result = dynamic_cast<Designtime::BluePrintEnum*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
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
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol found");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		++token;

		TokenIterator tmp = token;
		++tmp;
		if ( tmp->type() != Token::Type::IDENTIFER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		++token;
	}

	return result;
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

		++start;	// consume operator token

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

		++start;	// consume operator token

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
/*
		case Token::Type::BRACKET_OPEN: {
			++start;	// consume operator token

			Object tmp;
			expression(&tmp, start);

			expect(Token::Type::BRACKET_CLOSE, start);

			operator_trinary_array(result, &tmp, result);

			++start;	// consume operator token
		} break;
*/
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
			else if ( symbol->getSymbolType() == Symbol::IType::BluePrintEnumSymbol || symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
				PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(start);

				compareType = dynamic_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename();
				compareType = Designtime::Parser::buildRuntimeConstraintTypename(compareType, constraints);
			}
			else {
				throw Common::Exceptions::SyntaxError("invalid symbol type found", start->position());
			}

			*result = BoolObject(operator_binary_is(result, compareType));
		} break;
		case Token::Type::OPERATOR_NOT: {
			operator_unary_validate(result);
			++start;
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
			++start;
		} break;
		case Token::Type::CONST_DOUBLE: {
			DoubleObject tmp(Tools::stringToDouble(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_FLOAT: {
			FloatObject tmp(Tools::stringToFloat(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_INTEGER: {
			IntegerObject tmp(Tools::stringToInt(start->content()));
			operator_binary_assign(result, &tmp);
			++start;
		} break;
		case Token::Type::CONST_LITERAL: {
			StringObject tmp(start->content());
			operator_binary_assign(result, &tmp);
			++start;
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
					++start;
					break;
				case Symbol::IType::ObjectSymbol:
					operator_binary_assign(result, static_cast<Object*>(symbol));
					++start;
					break;
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::BluePrintObjectSymbol: {
					++start;

					PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(start);

					std::string newType = dynamic_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename();
								newType = Designtime::Parser::buildRuntimeConstraintTypename(newType, constraints);

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
			process_keyword(start, result);
			++start;
		} break;
		case Token::Type::SEMICOLON: {
		} break;
		default: {
			throw Common::Exceptions::SyntaxError("identifier, literal or constant expected but " + start->content() + " found", start->position());
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
	while ( ( (token != getTokens().end()) && (token != end) ) &&
			( (token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE) ) ) {

		if ( mControlFlow != ControlFlow::Normal ) {
			break;		// control flow has been broken, time to stop processing
		}

		mDebugger->notify(getScope(), (*token));		// notify debugger

		//process_statement(token, result);

		switch ( token->type() ) {
			case Token::Type::IDENTIFER:
			case Token::Type::PROTOTYPE:
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
				break;
			default:
				throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;	// consume token
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
void Interpreter::process_break(TokenIterator& token)
{
	if ( !mStack->current()->allowBreakAndContinue() ) {
		OSwarn("break not allowed in " + token->position().toString());
		return;
	}

	mControlFlow = ControlFlow::Break;
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
			Object *object = static_cast<Object*>(symbol);

			object->assign(Object());
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
	expect(Token::Type::PARENTHESIS_OPEN, token);

	TokenIterator initializationBegin = ++token;
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
	process(&declarationTmp, initializationBegin, conditionBegin);
	// }

	++bodyBegin;		// don't collect scope token
	token = bodyEnd;

	TokenList loopTokens;
	while ( bodyBegin != bodyEnd ) {
		loopTokens.push_back((*bodyBegin));
		++bodyBegin;
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
		mControlFlow = interpret(loopTokens, result, true);

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
		TokenIterator exprBegin = increaseBegin;

		Object expressionTmp;
		process(&expressionTmp, exprBegin, expressionEnd, Token::Type::PARENTHESIS_CLOSE);
		// }
	}
}

/*
 * syntax:
 * for ( <type definition> <identifier> : <instance> ) { ... }
 */
void Interpreter::process_foreach(TokenIterator& token, Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	TokenIterator typedefIt = token;

	// identify the loop variable's type
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + typedefIt->content() + "' not found", token->position());
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol && symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", token->position());
	}
	++token;

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(token);
	(void)constraints;

	expect(Token::Type::IDENTIFER, token);
	++token;
	expect(Token::Type::COLON, token);
	++token;
	expect(Token::Type::IDENTIFER, token);

	// identify collection symbol
	Object* collection = dynamic_cast<Object*>(identify(token));
	if ( !collection ) {
		throw Common::Exceptions::SyntaxError("invalid symbol '" + token->content() + "' found", token->position());
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

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyBegin = token;
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	++bodyBegin;		// don't collect scope token
	token = bodyEnd;

	TokenList loopTokens;
	while ( bodyBegin != bodyEnd ) {
		loopTokens.push_back((*bodyBegin));
		++bodyBegin;
	}

	for ( ; ; ) {
		pushScope();	// needed for loop variable

		// Setup
		// {
		Object tmp;
		iterator.execute(&tmp, "hasNext", ParameterList());

		if ( !isTrue(tmp) ) {	// do we have more items to iterate over?
			break;
		}

		// create and define loop variable
		TokenIterator typedefItCopy = typedefIt;
		Object* loop = process_type(typedefItCopy, symbol, false);

		// get current item
		iterator.execute(loop, "next", ParameterList());
		// }

		// Body parsing
		// {
		mControlFlow = interpret(loopTokens, result, true);

		popScope();	// needed for loop variable

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
		if ( symbol->getSymbolType() == Symbol::IType::BluePrintEnumSymbol || symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
			process_type(token, symbol);
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

			//if ( object->isMember() && dynamic_cast<Common::Method*>(mOwner)->isConst() ) {	// we tried to modify a member in a const method
			//	throw Common::Exceptions::ConstCorrectnessViolated("tried to modify member '" + object->getName() + "' in const method '" + getScope()->getScopeName() + "'", token->position());
			//}

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
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	++bodyBegin;		// don't collect scope token
	token = bodyEnd;	// no matter what, at least set our token to our if-block's end

	// collect all tokens for our if-block
	TokenList ifTokens;
	while ( bodyBegin != bodyEnd ) {
		ifTokens.push_back((*bodyBegin));
		++bodyBegin;
	}

	if ( bodyEnd != getTokens().end() ) {
		++bodyEnd;
	}

	bool targetReached = true;	// initially don't collect else-block tokens
	TokenIterator elseBegin = getTokens().end();
	TokenIterator elseEnd = getTokens().end();

	// look for an else-token
	if ( bodyEnd != getTokens().end() && (bodyEnd->type() == Token::Type::KEYWORD && bodyEnd->content() == KEYWORD_ELSE ) ) {
		elseBegin = findNext(bodyEnd, Token::Type::BRACKET_CURLY_OPEN);
		// find next balanced '{' & '}' pair
		elseEnd = findNextBalancedCurlyBracket(elseBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		for ( ; ; ) {
			// check if there is another if after our else-block
			TokenIterator tmpIf = elseEnd;
			++tmpIf;
			if ( tmpIf != getTokens().end() && tmpIf->type() == Token::Type::KEYWORD && tmpIf->content() == KEYWORD_ELSE ) {
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
		++elseBegin;
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

	Symbol* symbol = identifyMethod(token, params);

	Common::Method* method = dynamic_cast<Common::Method*>(symbol);
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
	Common::Method* owner = dynamic_cast<Common::Method*>(getEnclosingMethodScope());
	if ( owner && owner->isConst() ) {
		if ( owner->getEnclosingScope() == method->getEnclosingScope() && !method->isConst() ) {
			// check target method's constness
			// this is a const method and we want to call a non-const method... neeeeey!
			throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + getScope()->getFullScopeName() + "'", token->position());
		}
	}

	// static method check
	if ( owner && owner->isStatic() && !method->isStatic() ) {
		throw Runtime::Exceptions::StaticException("non-static method \"" + method->ToString() + "\" called from static method \"" + owner->ToString() + "\"", token->position());
	}

	ControlFlow::E controlflow;

	if ( method->isExtensionMethod() ) {
		controlflow = method->execute(params, result, (*token));
	}
	else {
		controlflow = execute(method, params, result);
	}

	switch ( controlflow ) {
		case ControlFlow::ExitProgram:
			mControlFlow = ControlFlow::ExitProgram;
			break;
		case ControlFlow::Throw:
			mControlFlow = ControlFlow::Throw;
			throw ControlFlow::Throw;			// throw even further
		default:
			mControlFlow = ControlFlow::Normal;
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

	token++;

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(token);

	expect(Token::Type::PARENTHESIS_OPEN, token);

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

	// create initialized reference of new object
	*result = *mRepository->createReference(static_cast<Designtime::BluePrintGeneric*>(symbol), name, constraints, Repository::InitilizationType::Final);

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

/*
		Object tmp(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, static_cast<Method*>(getEnclosingMethodScope(getScope()))->QualifiedTypename(), Runtime::AtomicValue());

		expression(&tmp, token);

		operator_binary_assign(result, &tmp);
*/
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
		++scopeBegin;
	}

	mControlFlow = interpret(scopeTokens, result);

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
}

/*
 * process a single statement
 */
void Interpreter::process_statement(TokenIterator& token, Object* result)
{
	switch ( token->type() ) {
		case Token::Type::IDENTIFER:
		case Token::Type::PROTOTYPE:
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
			break;
		default:
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}

	++token;	// consume token
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
	CaseBlock defaultBlock = CaseBlock(getTokens().end(), getTokens().end());

	// collect all case-blocks for further processing
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
		++bodyBegin;
	}

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
			expect(Token::Type::COLON, it->mBegin++);
			expect(Token::Type::BRACKET_CURLY_OPEN, it->mBegin++);	// don't collect scope token

			// collect case-block tokens
			TokenList caseTokens;
			while ( it->mBegin != it->mEnd ) {
				caseTokens.push_back((*it->mBegin));
				it->mBegin++;
			}

			// process/interpret case-block tokens
			mControlFlow = interpret(caseTokens, result, true);

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

		// process/interpret case-block tokens
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
		Object* data = mRepository->createInstance(OBJECT, ANONYMOUS_OBJECT, PrototypeConstraints());
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

	// notify our debugger that an exception has been thrown
	mDebugger->notifyExceptionThrow(getScope(), (*token));
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

	++tryBegin;	// don't collect scope tokens
	token = tryEnd;

	// collect try-block tokens
	TokenList tryTokens;
	while ( tryBegin != tryEnd ) {
		tryTokens.push_back((*tryBegin));
		++tryBegin;
	}

	// process try-block
	mControlFlow = interpret(tryTokens, result);

	TokenIterator tmp = lookahead(token, 1);

	std::list<TokenIterator> catches;
	TokenIterator finallyToken = getTokens().end();

	// collect all catch- and finally-blocks
	for ( ; ; ) {
		if ( tmp != getTokens().end() && tmp->content() == KEYWORD_CATCH ) {
			catches.push_back(tmp);

			tmp = findNextBalancedCurlyBracket(tmp, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			if ( std::distance(token, tmp) ) {
				token = tmp;	// set exit token
			}
		}
		else if ( tmp != getTokens().end() && tmp->content() == KEYWORD_FINALLY ) {
			if ( finallyToken != getTokens().end() ) {
				throw Common::Exceptions::SyntaxError("multiple finally blocks are not allowed");
			}

			finallyToken = tmp;
			tmp = findNextBalancedCurlyBracket(tmp, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

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
				if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol && symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
					throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", catchIt->position());
				}

				// create new exception type instance
				Object* type = process_type(catchIt, symbol, false);

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
			mDebugger->notifyExceptionCatch(getScope(), (*catchIt));

			expect(Token::Type::BRACKET_CURLY_OPEN, catchIt);

			// find next open curly bracket '{'
			TokenIterator catchBegin = catchIt;
			// find next balanced '{' & '}' pair
			TokenIterator catchEnd = findNextBalancedCurlyBracket(catchBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			++catchBegin;		// don't collect scope token

			// collect catch-block tokens
			TokenList catchTokens;
			while ( catchBegin != catchEnd ) {
				catchTokens.push_back((*catchBegin));
				++catchBegin;
			}

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

	// process finally-block (if present)
	if ( finallyToken != getTokens().end() ) {
		++finallyToken;
		expect(Token::Type::BRACKET_CURLY_OPEN, finallyToken);

		// find next open curly bracket '{'
		TokenIterator finallyBegin = finallyToken;
		// find next balanced '{' & '}' pair
		TokenIterator finallyEnd = findNextBalancedCurlyBracket(finallyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		++finallyBegin;		// don't collect scope token;

		// collect finally-block tokens
		TokenList finallyTokens;
		while ( finallyBegin != finallyEnd ) {
			finallyTokens.push_back((*finallyBegin));
			++finallyBegin;
		}

		// TODO: should we execute the finally-block in any case (i.e. even though a return has been issued by the user)?
		if ( mControlFlow == ControlFlow::Normal ) {
			mControlFlow = interpret(finallyTokens, result);
		}
	}
}

/*
 * syntax:
 * <type> [ "<" <type> ">" ] <identifier> [= <initialization>]
 */
Object* Interpreter::process_type(TokenIterator& token, Symbol* symbol, bool allowInitialization)
{
	bool isConst = false;
	bool isReference = false;

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(++token);

	expect(Token::Type::IDENTIFER, token);

	std::string name = (token++)->content();

	if ( token->type() == Token::Type::MODIFIER ) {
		if ( token->content() == MODIFIER_CONST ) { isConst = true; }
		else if ( token->content() == MODIFIER_MODIFY ) { isConst = false; }
		else {
			// invalid modifier
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	if ( token->type() == Token::Type::RESERVED_WORD ) {
		if ( token->content() == RESERVED_WORD_BY_REFERENCE ) { isReference = true; }
		else if ( token->content() == RESERVED_WORD_BY_VALUE ) { isReference = false; }
		else {
			// invalid type
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	TokenIterator assign = getTokens().end();
	if ( token->type() == Token::Type::ASSIGN ) {
		if ( !allowInitialization ) {
			// type declaration without initialization has been requested
			throw Common::Exceptions::NotSupported("type initialization is not allowed here", token->position());
		}

		assign = ++token;
	}


	Object* object = mRepository->createInstance(static_cast<Designtime::BluePrintGeneric*>(symbol), name, constraints);
	object->setConst(isConst);

	getScope()->define(name, object);

	if ( assign != getTokens().end() ) {
		// execute assignment statement
		try {
			Object tmp;
			expression(&tmp, token);

			if ( isReference && !tmp.getReference().isValid() ) {
				throw Runtime::Exceptions::InvalidAssignment("reference type expected", token->position());
			}
/* temporarily disabled
			else if ( !isReference && tmp.getReference().isValid() ) {
				throw Runtime::Exceptions::InvalidAssignment("value type expected", token->position());
			}
*/

			operator_binary_assign(object, &tmp);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return 0;
		}
	}

	return object;
}

/*
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
		case Symbol::IType::BluePrintEnumSymbol:
		case Symbol::IType::BluePrintObjectSymbol:
			*result = StringObject(static_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename());
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

	++bodyBegin;	// don't collect scope token;
	token = bodyEnd;

	TokenList whileTokens;
	while ( bodyBegin != bodyEnd ) {
		whileTokens.push_back((*bodyBegin));
		++bodyBegin;
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

		mControlFlow = interpret(whileTokens, result, true);

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
