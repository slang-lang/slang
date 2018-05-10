
// Header
#include "TreeInterpreter.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Utils.h>

// Namespace declarations

#define DEBUGGER(exp) \
	if ( mDebugger ) { \
		mDebugger->exp; \
	}

#define tryControl( exp ) \
		try { \
			exp; \
		} \
		catch ( Runtime::ControlFlow::E &e ) { \
			mControlFlow = e; \
			return; \
		}

#define tryEvalute(left, right) \
		try { \
			evaluate(left, right); \
		} \
		catch ( Runtime::ControlFlow::E &e ) { \
			mControlFlow = e; \
			return; \
		}

#define tryEvaluteReturnNull(left, right) \
		try { \
			evaluate(left, right); \
		} \
		catch ( Runtime::ControlFlow::E &e ) { \
			mControlFlow = e; \
			return NULL; \
		}


namespace ObjectiveScript {
namespace AST {


TreeInterpreter::TreeInterpreter(Common::ThreadId id)
: mControlFlow(Runtime::ControlFlow::Normal)
{
	// initialize virtual machine stuff
	mDebugger = Core::Debugger::Instance().useDebugger() ? &Core::Debugger::Instance() : NULL;
	mMemory = Controller::Instance().memory();
	mRepository = Controller::Instance().repository();
	mStack = Controller::Instance().thread(id);
}

TreeInterpreter::~TreeInterpreter()
{
}

void TreeInterpreter::deinitialize()
{
	// unwind stack
	mStack->pop();
}

void TreeInterpreter::evaluate(Node* exp, Runtime::Object* result)
{
	if ( !exp ) {
		throw Common::Exceptions::Exception("invalid expression");
	}
	if ( exp->getNodeType() != Node::NodeType::Expression ) {
		throw Common::Exceptions::Exception("not a valid expression type set");
	}

	switch ( static_cast<Expression*>(exp)->getExpressionType() ) {
		case Expression::ExpressionType::BinaryExpression: evaluateBinaryExpression(static_cast<BinaryExpression*>(exp), result); break;
		case Expression::ExpressionType::CopyExpression: evaluateCopyExpression(static_cast<CopyExpression*>(exp), result); break;
		case Expression::ExpressionType::IsExpression: evaluateIsExpression(static_cast<IsExpression*>(exp), result); break;
		case Expression::ExpressionType::LiteralExpression: evaluateLiteral(static_cast<LiteralExpression*>(exp), result); break;
		case Expression::ExpressionType::MethodExpression: evaluateMethodExpression(static_cast<MethodExpression*>(exp), result); break;
		case Expression::ExpressionType::NewExpression: evaluateNewExpression(static_cast<NewExpression*>(exp), result); break;
		case Expression::ExpressionType::SymbolExpression: evaluateSymbolExpression(static_cast<SymbolExpression *>(exp), result, getScope()); break;
		case Expression::ExpressionType::TernaryExpression: evaluateTernaryExpression(static_cast<TernaryExpression*>(exp), result); break;
		case Expression::ExpressionType::TypecastExpression: evaluateTypeCastExpression(static_cast<TypecastExpression*>(exp), result); break;
		case Expression::ExpressionType::TypeidExpression: evaluateTypeidExpression(static_cast<TypeidExpression*>(exp), result); break;
		case Expression::ExpressionType::UnaryExpression: evaluateUnaryExpression(static_cast<UnaryExpression*>(exp), result); break;
	}
}

void TreeInterpreter::evaluateBinaryExpression(BinaryExpression* exp, Runtime::Object* result)
{
	if ( exp->getBinaryExpressionType() == BinaryExpression::BinaryExpressionType::BooleanBinaryExpression ) {
		return evaluateBooleanBinaryExpression(static_cast<BooleanBinaryExpression*>(exp), result);
	}

	Runtime::Object left;
	// evaluate left expression
	evaluate(exp->mLeft, &left);

	Runtime::Object right;
	// evaluate right expression
	evaluate(exp->mRight, &right);

	switch ( exp->mOperation.type() ) {
		// bit expressions
		// {
		case Token::Type::BITAND: Runtime::operator_binary_bitand(&left, &right); break;
		case Token::Type::BITCOMPLEMENT: Runtime::operator_binary_bitcomplement(&left, &right); break;
		case Token::Type::BITOR: Runtime::operator_binary_bitor(&left, &right); break;
		// }

		// math expressions
		// {
		case Token::Type::MATH_ADDITION: Runtime::operator_binary_plus(&left, &right); break;
		case Token::Type::MATH_DIVIDE: Runtime::operator_binary_divide(&left, &right); break;
		case Token::Type::MATH_MODULO: Runtime::operator_binary_modulo(&left, &right); break;
		case Token::Type::MATH_MULTIPLY: Runtime::operator_binary_multiply(&left, &right); break;
		case Token::Type::MATH_SUBTRACT: Runtime::operator_binary_subtract(&left, &right); break;
		// }

		// default handling
		// {
		default: throw Common::Exceptions::NotSupported("binary expression with " + exp->mOperation.content() + " not supported");
		// }
	}

	// assign (left ? right) to result
	Runtime::operator_binary_assign(result, &left);
}

void TreeInterpreter::evaluateBooleanBinaryExpression(BooleanBinaryExpression* exp, Runtime::Object* result)
{
	Runtime::Object left;

	// evaluate left expression
	evaluate(exp->mLeft, &left);

	bool leftResult = isTrue(left);

	// incomplete boolean evaluation
	if ( exp->mOperation.type() == Token::Type::AND && !leftResult ) {
		*result = Runtime::BoolObject(false);
		return;
	}
	else if ( exp->mOperation.type() == Token::Type::NAND && !leftResult ) {
		*result = Runtime::BoolObject(true);
		return;
	}
	else if ( exp->mOperation.type() == Token::Type::NOR && leftResult ) {
		*result = Runtime::BoolObject(false);
		return;
	}
	else if ( exp->mOperation.type() == Token::Type::OR && leftResult ) {
		*result = Runtime::BoolObject(true);
		return;
	}

	Runtime::Object right;

	// evaluate right expression
	evaluate(exp->mRight, &right);

	switch ( exp->mOperation.type() ) {
		// boolean expressions
		// {
		case Token::Type::AND: *result = Runtime::BoolObject(leftResult && isTrue(right)); break;
		case Token::Type::NAND: *result = Runtime::BoolObject(!leftResult && !isTrue(right)); break;
		case Token::Type::NOR: *result = Runtime::BoolObject(!leftResult || !isTrue(right)); break;
		case Token::Type::OR: *result = Runtime::BoolObject(leftResult || isTrue(right)); break;
		// }

		// comparison expressions
		// {
		case Token::Type::COMPARE_EQUAL: *result = Runtime::BoolObject(operator_binary_equal(&left, &right)); break;
		case Token::Type::COMPARE_GREATER: *result = Runtime::BoolObject(operator_binary_greater(&left, &right)); break;
		case Token::Type::COMPARE_GREATER_EQUAL: *result = Runtime::BoolObject(operator_binary_greater_equal(&left, &right)); break;
		case Token::Type::COMPARE_LESS: *result = Runtime::BoolObject(operator_binary_less(&left, &right)); break;
		case Token::Type::COMPARE_LESS_EQUAL: *result = Runtime::BoolObject(operator_binary_less_equal(&left, &right)); break;
		case Token::Type::COMPARE_UNEQUAL: *result = Runtime::BoolObject(!operator_binary_equal(&left, &right)); break;
		// }

		// default handling
		// {
		default: throw Common::Exceptions::NotSupported("binary expression with " + exp->mOperation.content() + " not supported");
		// }
	}
}

void TreeInterpreter::evaluateCopyExpression(CopyExpression* exp, Runtime::Object* result)
{
	Runtime::Object obj;

	evaluate(exp->mExpression, &obj);

	result->copy(obj);
}

void TreeInterpreter::evaluateIsExpression(IsExpression* exp, Runtime::Object* result)
{
	Runtime::Object tmp;

	// evaluate left expression
	evaluate(exp->mExpression, &tmp);

	*result = Runtime::BoolObject(tmp.isInstanceOf(exp->mMatchType));
}

void TreeInterpreter::evaluateLiteral(LiteralExpression* exp, Runtime::Object* result)
{
	switch ( exp->mValue.type() ) {
		case Runtime::AtomicValue::Type::BOOL: *result = Runtime::BoolObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::DOUBLE: *result = Runtime::DoubleObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::FLOAT: *result = Runtime::FloatObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::INT: *result = Runtime::IntegerObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::REFERENCE: *result = *mMemory->get(Runtime::Reference(exp->mValue.toReference())); break;
		case Runtime::AtomicValue::Type::STRING: *result = Runtime::StringObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::UNKOWN: throw Common::Exceptions::NotSupported("UNKNOWN type");
	}
}

void TreeInterpreter::evaluateMethodExpression(MethodExpression* exp, Runtime::Object* result)
{
	std::list<Runtime::Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	for ( ExpressionList::const_iterator it = exp->mParams.begin(); it != exp->mParams.end(); ++it ) {
		objectList.emplace_back(Runtime::Object());

		Runtime::Object* param = &objectList.back();

		evaluate((*it), param);

		params.push_back(Parameter::CreateRuntime(param->QualifiedOuterface(), param->getValue(), param->getReference()));
	}

	IScope* scope = getScope();

	MethodSymbol* methodSymbol = resolveMethod(scope, exp->mSymbolExpression, params, Visibility::Private);
	if ( !methodSymbol ) {
		methodSymbol = resolveMethod(getEnclosingMethodScope(scope), exp->mSymbolExpression, params, Visibility::Private);
	}
	if ( !methodSymbol ) {
		throw Runtime::Exceptions::RuntimeException("method " + exp->mSymbolExpression->toString() + "(" + toString(params) + ") not found");
	}

	Common::Method* method = dynamic_cast<Common::Method*>(methodSymbol);
	assert(method);

	if ( method->isExtensionMethod() ) {
		mControlFlow = method->execute(params, result, Token());
	}
	else {
		mControlFlow = execute(method, params, result);
	}

	switch ( mControlFlow ) {
		case Runtime::ControlFlow::ExitProgram: throw Runtime::ControlFlow::ExitProgram;	// promote control flow
		case Runtime::ControlFlow::Throw: throw Runtime::ControlFlow::Throw;				// promote control flow
		default: mControlFlow = Runtime::ControlFlow::Normal; break;
	}
}

void TreeInterpreter::evaluateNewExpression(NewExpression* exp, Runtime::Object* result)
{
	MethodExpression* method = dynamic_cast<MethodExpression*>(exp->mExpression);
	if ( !method ) {
		throw Runtime::Exceptions::RuntimeException("invalid method expression found");
	}

	std::list<Runtime::Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	for ( ExpressionList::const_iterator it = method->mParams.begin(); it != method->mParams.end(); ++it ) {
		objectList.emplace_back(Runtime::Object());

		Runtime::Object* param = &objectList.back();

		evaluate((*it), param);

		params.push_back(Parameter::CreateRuntime(param->QualifiedOuterface(), param->getValue(), param->getReference()));
	}

	// create initialized reference of new object
	*result = *mRepository->createReference(exp->getResultType(), ANONYMOUS_OBJECT, PrototypeConstraints(), Repository::InitilizationType::Final);

	// execute new object's constructor
	mControlFlow = result->Constructor(params);
}

void TreeInterpreter::evaluateSymbolExpression(SymbolExpression *exp, Runtime::Object *result, IScope *scope)
{
	if ( !scope ) {
		throw Common::Exceptions::Exception("invalid scope provided");
	}

	// resolve current symbol name
	Symbol* lvalue = scope->resolve(exp->mName, false, Visibility::Designtime);
	if ( !lvalue ) {
		throw Runtime::Exceptions::InvalidAssignment("lvalue '" + exp->mName + "' not found");
	}

	// evaluate sub expression?
	if ( exp->mSymbolExpression ) {
		switch ( lvalue->getSymbolType() ) {
			case Symbol::IType::BluePrintObjectSymbol:
				scope = static_cast<Designtime::BluePrintObject*>(lvalue);
				break;
			case Symbol::IType::NamespaceSymbol:
				scope = static_cast<Common::Namespace*>(lvalue);
				break;
			case Symbol::IType::ObjectSymbol:
				scope = static_cast<Runtime::Object*>(lvalue);
				break;
			case Symbol::IType::MethodSymbol:
				throw Common::Exceptions::NotSupported("cannot directly access locales of method");
		}

		return evaluateSymbolExpression(exp->mSymbolExpression, result, scope);
	}

	if ( lvalue->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Runtime::Exceptions::RuntimeException("invalid lvalue symbol type");
	}

	*result = *static_cast<Runtime::Object*>(lvalue);
}

void TreeInterpreter::evaluateTernaryExpression(TernaryExpression* exp, Runtime::Object* result)
{
	Runtime::Object condition;

	// evaluate ? condition
	evaluate(exp->mCondition, &condition);

	// validate ? condition
	if ( isTrue(condition) ) {
		evaluate(exp->mFirst, result);
	}
	else {
		evaluate(exp->mSecond, result);
	}
}

void TreeInterpreter::evaluateTypeCastExpression(TypecastExpression* exp, Runtime::Object* result)
{
	Runtime::Object tmp;

	evaluate(exp->mExpression, &tmp);

	Runtime::typecast(&tmp, exp->mDestinationType);

	Runtime::operator_binary_assign(result, &tmp);
}

void TreeInterpreter::evaluateTypeidExpression(TypeidExpression* exp, Runtime::Object* result)
{
	Runtime::Object tmp;

	evaluate(exp->mExpression, &tmp);

	Runtime::StringObject type(Runtime::AtomicValue(tmp.QualifiedTypename()));
	Runtime::operator_binary_assign(result, &type);
}

void TreeInterpreter::evaluateUnaryExpression(UnaryExpression* exp, Runtime::Object* result)
{
	if ( exp->mValueType == UnaryExpression::ValueType::LValue ) {
		Runtime::Object &lvalue = resolveLValue(getScope(), dynamic_cast<SymbolExpression*>(exp->mExpression), false, Visibility::Designtime);

		switch ( exp->mOperation.type() ) {
			// math expressions
			// {
			case Token::Type::OPERATOR_DECREMENT: Runtime::operator_unary_decrement(&lvalue, exp->mOperation.position()); break;
			case Token::Type::OPERATOR_INCREMENT: Runtime::operator_unary_increment(&lvalue, exp->mOperation.position()); break;
			// }

			// subscript operator
			// {
			case Token::Type::BRACKET_OPEN: evaluate(exp->mExpression, &lvalue); break;
			// }

			// default handling
			// {
			default: throw Common::Exceptions::NotSupported("lvalue expression with " + exp->mOperation.content() + " not supported");
			// }
		}

		Runtime::operator_binary_assign(result, &lvalue);
	}
	else {
		evaluate(exp->mExpression, result);

		switch ( exp->mOperation.type() ) {
			// boolean expressions
			// {
			case Token::Type::OPERATOR_NOT: Runtime::operator_unary_not(result, exp->mOperation.position()); break;
			case Token::Type::OPERATOR_VALIDATE: Runtime::operator_unary_validate(result, exp->mOperation.position()); break;
			// }

			// math expressions
			// {
			case Token::Type::MATH_ADDITION: /* nothing to do here */ break;
			case Token::Type::MATH_SUBTRACT: Runtime::operator_unary_minus(result, exp->mOperation.position()); break;
			case Token::Type::OPERATOR_DECREMENT: Runtime::operator_unary_decrement(result, exp->mOperation.position()); break;
			case Token::Type::OPERATOR_INCREMENT: Runtime::operator_unary_increment(result, exp->mOperation.position()); break;
			// }

			// subscript operator
			// {
			case Token::Type::BRACKET_OPEN: evaluate(exp->mExpression, result); break;
			// }

			// default handling
			// {
			default: throw Common::Exceptions::NotSupported("rvalue expression with " + exp->mOperation.content() + " not supported", exp->mOperation.position());
			// }
		}
	}
}

Runtime::ControlFlow::E TreeInterpreter::execute(Common::Method* method, const ParameterList& params, Runtime::Object* result)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method pointer provided!");
	}
	if ( method->isAbstract() ) {
		throw Common::Exceptions::AbstractException("cannot execute abstract method '" + method->getFullScopeName() + "'");
	}

	Common::Method scope(*method);

	// initialize parameters & push scope
	initialize(&scope, method->mergeParameters(params));

	// notify debugger
	DEBUGGER( notifyEnter(&scope, Core::Debugger::immediateBreakToken) );

	// interpret scope tokens
	process(method->getRootNode());

	// notify debugger
	DEBUGGER( notifyExit(&scope, Core::Debugger::immediateBreakToken) );

	// only set return value if we are a non-void method
	if ( result && method->QualifiedTypename() != _void ) {
		*result = mStack->current()->returnValue();
	}

	// deinitalize & pop scope
	deinitialize();

	return mControlFlow;
}

MethodScope* TreeInterpreter::getEnclosingMethodScope(IScope *scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			return dynamic_cast<MethodScope*>(parent);
		}

		scope = parent;
	}

	return 0;
}

NamedScope* TreeInterpreter::getEnclosingNamedScope(IScope *scope) const
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

Common::Namespace* TreeInterpreter::getEnclosingNamespace(IScope* scope) const
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

Runtime::Object* TreeInterpreter::getEnclosingObject(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Runtime::Object* result = dynamic_cast<Runtime::Object*>(parent);
			if ( result ) {
				return result;
			}
		}

		scope = parent;
	}

	return 0;
}

inline IScope* TreeInterpreter::getScope() const
{
	return mStack->current()->getScope();
}

void TreeInterpreter::initialize(IScope* scope, const ParameterList& params)
{
	// add parameters as locale variables
	for ( ParameterList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		if ( it->name().empty() ) {
			// skip unnamed parameters
			continue;
		}

		Runtime::Object* object = mRepository->createInstance(it->type(), it->name());

		object->setMutability(it->mutability());
		object->setValue(it->value());

		switch ( it->access() ) {
			case AccessMode::ByReference: {
				object->setIsReference(true);

				if ( it->reference().isValid() ) {
					object->assign(*mMemory->get(it->reference()));
				}
			} break;
			case AccessMode::ByValue: {
				object->setIsReference(false);

				if ( it->reference().isValid() ) {
					throw Common::Exceptions::NotSupported("by value calls not allowed for objects");
				}
			} break;
			case AccessMode::Unspecified:
				throw Common::Exceptions::AccessMode("unspecified access mode");
		}

		scope->define(it->name(), object);
	}

	// record stack
	mStack->push(scope, TokenList(), params);
}

void TreeInterpreter::popScope()
{
	mStack->current()->popScope();
}

std::string TreeInterpreter::printExpression(Node* node) const
{
	if ( !node ) {
		return "";
	}

	assert(node->getNodeType() == Node::NodeType::Expression);

	Expression* expression = dynamic_cast<Expression*>(node);
	std::string result;

	switch ( expression->getExpressionType() ) {
		case Expression::ExpressionType::BinaryExpression: {
			BinaryExpression* bin = dynamic_cast<BinaryExpression*>(node);

			result += "(" + printExpression(bin->mLeft);
			result += " " + bin->mOperation.content() + " ";
			result += printExpression(bin->mRight) + ")";
		} break;
		case Expression::ExpressionType::CopyExpression: {
			result += "copy " + printExpression(dynamic_cast<CopyExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::IsExpression: {
			result += printExpression(dynamic_cast<IsExpression*>(expression)->mExpression) + " is " + dynamic_cast<IsExpression*>(expression)->mMatchType;
		} break;
		case Expression::ExpressionType::NewExpression: {
			result += "new " + printExpression(dynamic_cast<NewExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::LiteralExpression: {
			result += dynamic_cast<LiteralExpression*>(expression)->mValue.toStdString();
		} break;
		case Expression::ExpressionType::MethodExpression: {
			result += printExpression(dynamic_cast<MethodExpression*>(expression)->mSymbolExpression);
			result += "(";
			for ( ExpressionList::const_iterator it = dynamic_cast<MethodExpression*>(expression)->mParams.begin(); it != dynamic_cast<MethodExpression*>(expression)->mParams.end(); ++it ) {
				result += printExpression((*it));
			}
			result += ")";
		} break;
		case Expression::ExpressionType::SymbolExpression: {
			if ( dynamic_cast<SymbolExpression*>(expression)->mSymbolExpression ) {
				result += printExpression(dynamic_cast<SymbolExpression*>(expression)->mSymbolExpression);
			}
			else {
				result += dynamic_cast<SymbolExpression*>(expression)->mName;
			}
		} break;
		case Expression::ExpressionType::TernaryExpression: {
			result += printExpression(dynamic_cast<TernaryExpression*>(expression)->mCondition) + " ? ";
			result += printExpression(dynamic_cast<TernaryExpression*>(expression)->mFirst) + " : ";
			result += printExpression(dynamic_cast<TernaryExpression*>(expression)->mSecond);
		} break;
		case Expression::ExpressionType::TypecastExpression: {
			result += dynamic_cast<TypecastExpression*>(expression)->mDestinationType + " ";
			result += printExpression(dynamic_cast<TypecastExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::TypeidExpression: {
			result += "typeid(" + printExpression(dynamic_cast<TypeidExpression*>(expression)->mExpression) + ")";
		} break;
		case Expression::ExpressionType::UnaryExpression: {
			UnaryExpression* bin = dynamic_cast<UnaryExpression*>(expression);

			result += bin->mOperation.content();
			result += printExpression(bin->mExpression);
		} break;
	}

	return result;
}

void TreeInterpreter::process(Statements* statements)
{
	if ( !statements ) {
		return;
	}

	for ( Statements::Nodes::const_iterator it = statements->mNodes.begin(); it != statements->mNodes.end(); ++it ) {
		if ( mControlFlow != Runtime::ControlFlow::Normal ) {
			break;		// control flow has been broken, time to stop processing
		}

		visit((*it));
	}
}

void TreeInterpreter::pushScope(IScope* scope)
{
	StackFrame* stack = mStack->current();

	bool allowDelete = !scope;
	if ( allowDelete ) {
		scope = new SymbolScope(stack->getScope());
	}

	stack->pushScope(scope, allowDelete, true);
}

Runtime::Object& TreeInterpreter::resolveLValue(IScope *scope, SymbolExpression *symbol, bool onlyCurrentScope, Visibility::E visibility) const
{
	Runtime::Object* result = dynamic_cast<Runtime::Object*>(resolveRValue(scope, symbol, onlyCurrentScope, visibility));
	if ( !result ) {
		throw Runtime::Exceptions::AccessViolation(symbol->toString());
	}

	return (*result);
}

Symbol* TreeInterpreter::resolveRValue(IScope *scope, SymbolExpression *symbol, bool onlyCurrentScope, Visibility::E visibility) const
{
	if ( !scope ) {
		throw Runtime::Exceptions::InvalidSymbol("invalid scope provided");
	}
	if ( !symbol ) {
		throw Runtime::Exceptions::InvalidSymbol("invalid symbol provided");
	}

	while ( symbol->mSymbolExpression ) {
		Symbol* child = scope->resolve(symbol->mName, onlyCurrentScope, visibility);

		if ( !child ) {
			return 0;
		}

		switch ( child->getSymbolType() ) {
			case Symbol::IType::BluePrintObjectSymbol:
				scope = static_cast<Designtime::BluePrintObject*>(child);
				break;
			case Symbol::IType::NamespaceSymbol:
				scope = static_cast<Common::Namespace*>(child);
				break;
			case Symbol::IType::ObjectSymbol:
				scope = static_cast<Runtime::Object*>(child);
				break;
			case Symbol::IType::MethodSymbol:
				throw Runtime::Exceptions::InvalidSymbol("invalid symbol type found");
		}

		symbol = symbol->mSymbolExpression;
	}

	return scope->resolve(symbol->mName, onlyCurrentScope, visibility);
}

MethodSymbol* TreeInterpreter::resolveMethod(IScope* scope, SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) const
{
	if ( !scope ) {
		throw Runtime::Exceptions::InvalidSymbol("invalid scope provided");
	}
	if ( !symbol ) {
		throw Runtime::Exceptions::InvalidSymbol("invalid symbol provided");
	}

	bool onlyCurrentScope = false;

	while ( symbol->mSymbolExpression ) {
		Symbol* child = scope->resolve(symbol->mName, onlyCurrentScope, visibility);
		onlyCurrentScope = true;

		if ( !child ) {
			return 0;
		}

		switch ( child->getSymbolType() ) {
			case Symbol::IType::BluePrintObjectSymbol:
				scope = static_cast<Designtime::BluePrintObject*>(child);
				break;
			case Symbol::IType::NamespaceSymbol:
				scope = static_cast<Common::Namespace*>(child);
				break;
			case Symbol::IType::ObjectSymbol:
				scope = static_cast<Runtime::Object*>(child);
				break;
			case Symbol::IType::MethodSymbol:
				throw Runtime::Exceptions::InvalidSymbol("invalid symbol type found: " + symbol->toString());
		}

		symbol = symbol->mSymbolExpression;
	}

	MethodScope* methodScope = dynamic_cast<MethodScope*>(scope);
	if ( !methodScope ) {
		return 0;
	}

	return methodScope->resolveMethod(symbol->mName, params, false, visibility);
}

void TreeInterpreter::visit(Node* node)
{
	if ( !node ) {
		return;
	}

	switch ( node->getNodeType() ) {
		case Node::NodeType::Expression:
			visitExpression(static_cast<Expression*>(node));
			break;
		case Node::NodeType::Operator:
			visitOperator(static_cast<Operator*>(node));
			break;
		case Node::NodeType::Statement:
			visitStatement(static_cast<Statement*>(node));
			break;
	}
}

void TreeInterpreter::visitAssert(AssertStatement* node)
{
	Runtime::Object condition;
	tryControl(evaluate(node->mExpression, &condition));

	if ( !isTrue(condition) ) {
		std::cout << "assert(" << printExpression(node->mExpression) << ");" << std::endl;

		throw Runtime::Exceptions::AssertionFailed(condition.ToString(), node->mPosition);
	}
}

void TreeInterpreter::visitAssignment(Assignment* node)
{
	Runtime::Object &lvalue = resolveLValue(getScope(), node->mLValue, false, Visibility::Designtime);

	Runtime::Object tmp;

	tryControl(evaluate(node->mExpression, &tmp));

	Runtime::operator_binary_assign(&lvalue, &tmp);
}

void TreeInterpreter::visitBreak(BreakStatement* /*node*/)
{
	mControlFlow = Runtime::ControlFlow::Break;
}

void TreeInterpreter::visitContinue(ContinueStatement* /*node*/)
{
	mControlFlow = Runtime::ControlFlow::Continue;
}

void TreeInterpreter::visitDelete(DeleteStatement* node)
{
	Runtime::Object obj;
	tryControl(evaluate(node->mExpression, &obj));

	obj = Runtime::Object();
}

void TreeInterpreter::visitExit(ExitStatement* node)
{
	Runtime::Object* data = mRepository->createInstance(Runtime::IntegerObject::TYPENAME, ANONYMOUS_OBJECT, PrototypeConstraints());
	tryControl(evaluate(node->mExpression, data));

	mStack->exception() = Runtime::ExceptionData(data, Common::Position());

	throw Runtime::ControlFlow::ExitProgram;
}

void TreeInterpreter::visitExpression(Expression* expression)
{
	Runtime::Object tmp;
	tryControl(evaluate(expression, &tmp));
}

void TreeInterpreter::visitFor(ForStatement* node)
{
	// execute initialization statement
	visitStatement(dynamic_cast<Statement*>(node->mInitialization));

	//pushScope();	// push new scope for loop variable

	Runtime::Object condition;
	for  ( ; ; ) {
		if ( node->mCondition ) {
			tryControl(evaluate(node->mCondition, &condition));		// evaluate loop condition

			// validate loop condition
			if ( !isTrue(condition) ) {
				break;
			}
		}

		// execute compound statement
		visitStatement(dynamic_cast<Statement*>(node->mStatement));

		// check (and reset) control flow
		switch ( mControlFlow ) {
			case Runtime::ControlFlow::Break: mControlFlow = Runtime::ControlFlow::Normal; return;
			case Runtime::ControlFlow::Continue: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::ExitProgram: mControlFlow = Runtime::ControlFlow::ExitProgram; return;
			case Runtime::ControlFlow::Normal: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::Return: mControlFlow = Runtime::ControlFlow::Return; return;
			case Runtime::ControlFlow::Throw: mControlFlow = Runtime::ControlFlow::Throw; return;
		}

		// execute arbitrary iteration node type
		visit(node->mIteration);
	}

	//popScope();		// pop scope and remove loop variable
}

void TreeInterpreter::visitForeach(ForeachStatement* node)
{
	Runtime::Object collection;
	tryControl(evaluate(node->mLoopExpression, &collection));

	// get collection's forward iterator
	Runtime::Object iterator;
	collection.execute(&iterator, "getIterator", ParameterList());

	for  ( ; ; ) {
		// Setup
		// {
		Runtime::Object condition;
		iterator.execute(&condition, "hasNext", ParameterList());

		if ( !isTrue(condition) ) {	// do we have more items to iterate over?
			break;
		}
		// }

		pushScope();	// push new scope for loop variable

		// execute type declaration
		// {
		TypeDeclaration* typeDeclaration = node->mTypeDeclaration;

		Runtime::Object* loopVariable = mRepository->createInstance(typeDeclaration->mType, typeDeclaration->mName, typeDeclaration->mConstraints);

		getScope()->define(typeDeclaration->mName, loopVariable);

		loopVariable->setConst(typeDeclaration->mIsConst);
		// }

		// iterate over next item
		iterator.execute(loopVariable, "next", ParameterList());

		// execute compound statement
		visitStatement(dynamic_cast<Statement*>(node->mStatement));

		popScope();		// pop scope and remove loop variable

		// check (and reset) control flow
		switch ( mControlFlow ) {
			case Runtime::ControlFlow::Break: mControlFlow = Runtime::ControlFlow::Normal; return;
			case Runtime::ControlFlow::Continue: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::ExitProgram: mControlFlow = Runtime::ControlFlow::ExitProgram; return;
			case Runtime::ControlFlow::Normal: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::Return: mControlFlow = Runtime::ControlFlow::Return; return;
			case Runtime::ControlFlow::Throw: mControlFlow = Runtime::ControlFlow::Throw; return;
		}
	}
}

void TreeInterpreter::visitIf(IfStatement* node)
{
	// evaluate if-condition
	Runtime::Object condition;
	tryControl(evaluate(node->mCondition, &condition));

	// validate if-condition
	if ( isTrue(condition) ) {
		// execute if-compound statement
		visitStatement(dynamic_cast<Statement*>(node->mIfBlock));
	}
	else {
		// execute else-compound statement
		visitStatement(dynamic_cast<Statement*>(node->mElseBlock));
	}
}

void TreeInterpreter::visitOperator(Operator* /*op*/)
{
	throw Common::Exceptions::SyntaxError("cannot process standalone operator");
}

void TreeInterpreter::visitPrint(PrintStatement* node)
{
	Runtime::Object text;
	tryControl(evaluate(node->mExpression, &text));

	::Utils::PrinterDriver::Instance()->print(text.getValue().toStdString(), node->mPosition.mFile, node->mPosition.mLine);
}

void TreeInterpreter::visitReturn(ReturnStatement* node)
{
	if ( node->mExpression ) {	// only process not-empty return statements
		Runtime::Object tmp;

		tryControl(evaluate(node->mExpression, &tmp));

		Runtime::operator_binary_assign(&mStack->current()->returnValue(), &tmp);
	}

	mControlFlow = Runtime::ControlFlow::Return;
}

void TreeInterpreter::visitStatement(Statement *node)
{
	if ( !node ) {
		return;
	}

	DEBUGGER( notify(getScope(), node->token()) );		// notify debugger

	switch ( node->getStatementType() ) {
		case Statement::StatementType::AssertStatement:
			visitAssert(dynamic_cast<AssertStatement*>(node));
			break;
		case Statement::StatementType::Assignment:
			visitAssignment(dynamic_cast<Assignment*>(node));
			break;
		case Statement::StatementType::BreakStatement:
			visitBreak(dynamic_cast<BreakStatement*>(node));
			break;
		case Statement::StatementType::CaseStatement:
			throw Common::Exceptions::Exception("case statements are handled separately!");
		case Statement::StatementType::CatchStatement:
			throw Common::Exceptions::Exception("catch statements are handled separately!");
		case Statement::StatementType::ContinueStatement:
			visitContinue(dynamic_cast<ContinueStatement*>(node));
			break;
		case Statement::StatementType::DeleteStatement:
			visitDelete(dynamic_cast<DeleteStatement*>(node));
			break;
		case Statement::StatementType::ExitStatement:
			visitExit(dynamic_cast<ExitStatement*>(node));
			break;
		case Statement::StatementType::ForeachStatement:
			visitForeach(dynamic_cast<ForeachStatement *>(node));
			break;
		case Statement::StatementType::ForStatement:
			visitFor(dynamic_cast<ForStatement*>(node));
			break;
		case Statement::StatementType::IfStatement:
			visitIf(dynamic_cast<IfStatement*>(node));
			break;
		case Statement::StatementType::PrintStatement:
			visitPrint(dynamic_cast<PrintStatement*>(node));
			break;
		case Statement::StatementType::ReturnStatement:
			visitReturn(dynamic_cast<ReturnStatement*>(node));
			break;
		case Statement::StatementType::Statements:
			visitStatements(dynamic_cast<Statements*>(node));
			break;
		case Statement::StatementType::SwitchStatement:
			visitSwitch(dynamic_cast<SwitchStatement*>(node));
			break;
		case Statement::StatementType::ThrowStatement:
			visitThrow(dynamic_cast<ThrowStatement*>(node));
			break;
		case Statement::StatementType::TryStatement:
			visitTry(dynamic_cast<TryStatement*>(node));
			break;
		case Statement::StatementType::TypeDeclaration:
			visitTypeDeclaration(dynamic_cast<TypeDeclaration*>(node));
			break;
		case Statement::StatementType::TypeInference:
			visitTypeInference(dynamic_cast<TypeInference*>(node));
			break;
		case Statement::StatementType::WhileStatement:
			visitWhile(dynamic_cast<WhileStatement*>(node));
			break;
	}
}

void TreeInterpreter::visitStatements(Statements* node)
{
	// push a new scope
	pushScope();

	// execute compound statement
	process(node);

	// pop current scope
	popScope();
}

void TreeInterpreter::visitSwitch(SwitchStatement* node)
{
	Runtime::Object value;

	do {
		// reset this for every loop
		bool caseMatched = false;
		bool evaluateCaseExpression = true;

		// loop over all case statements
		for ( CaseStatements::const_iterator it = node->mCaseStatements.begin(); it != node->mCaseStatements.end(); ++it ) {
			if ( evaluateCaseExpression ) {
				tryControl(evaluate(node->mExpression, &value));

				evaluateCaseExpression = false;
			}

			Runtime::Object caseValue;
			tryControl(evaluate((*it)->mCaseExpression, &caseValue));

			if ( Runtime::operator_binary_equal(&value, &caseValue) ) {
				caseMatched = true;

				visitStatements((*it)->mCaseBlock);
			}
		}

		// no matching case statement found => execute default statement
		if ( !caseMatched ) {
			visitStatements(node->mDefaultStatement);
		}

		// inspect control flow after the complete iteration
		switch ( mControlFlow ) {
			case Runtime::ControlFlow::Continue:
				mControlFlow = Runtime::ControlFlow::Normal;
				break;	// continue loop, reset current control flow state
			case Runtime::ControlFlow::Break:
			case Runtime::ControlFlow::Normal:
				mControlFlow = Runtime::ControlFlow::Normal;
				return;	// no further processing, reset current control flow state
			case Runtime::ControlFlow::ExitProgram:
			case Runtime::ControlFlow::Return:
			case Runtime::ControlFlow::Throw:
				return;	// no further processing, keep current control flow state
		}
	} while ( mControlFlow == Runtime::ControlFlow::Normal );
}

void TreeInterpreter::visitThrow(ThrowStatement* node)
{
	if ( node->mExpression ) {	// throw new expression
		Runtime::Object* data = mRepository->createInstance(_object, ANONYMOUS_OBJECT, PrototypeConstraints());
		tryControl(evaluate(node->mExpression, data));

		mStack->exception() = Runtime::ExceptionData(data, Common::Position());
	}

	mControlFlow = Runtime::ControlFlow::Throw;

	// notify our debugger that an exception has been thrown
	DEBUGGER( notifyExceptionThrow(getScope(), node->token()) );
}

void TreeInterpreter::visitTry(TryStatement* node)
{
	// execute try-block
	visitStatements(node->mTryBlock);

	// execute exception handling only if an exception occurred and catch statements are present
	if ( mControlFlow == Runtime::ControlFlow::Throw && !node->mCatchStatements.empty() ) {
		// get exception data
		Runtime::Object* exception = mStack->exception().getData();

		// determine correct catch-block (if a correct one exists)
		for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
			if ( (*it)->mTypeDeclaration && !exception->isInstanceOf((*it)->mTypeDeclaration->mType) ) {
				// exception type does not match
				continue;
			}

			// reset control flow to normal to allow execution of catch-block
			mControlFlow = Runtime::ControlFlow::Normal;

			// push a new scope to be able to clean up the exception variable
			pushScope();

			// process exception type declaration (if present)
			if ( (*it)->mTypeDeclaration ) {
				// retrieve exception instance variable
				Runtime::Object* symbol = visitTypeDeclaration((*it)->mTypeDeclaration);

				// assign exception to instance variable
				Runtime::operator_binary_assign(symbol, exception);
			}

			// notify our debugger that an exception has been caught
			DEBUGGER( notifyExceptionCatch(getScope(), (*it)->token()) );

			// execute catch statements
			visitStatements((*it)->mStatements);

			// pop scope to clean up the exception variable
			popScope();

			// only process one catch-block
			break;
		}
	}

	// store current control flow and re-set it after finally block has been executed
	Runtime::ControlFlow::E tmpControlFlow = mControlFlow;

	// reset current control flow to allow execution of finally-block
	mControlFlow = Runtime::ControlFlow::Normal;

	// execute finally-block if present
	if ( node->mFinallyBlock ) {
		visitStatements(node->mFinallyBlock);
	}

	// reset control flow to previous state if not set differently by finally statement
	if ( mControlFlow == Runtime::ControlFlow::Normal && tmpControlFlow != Runtime::ControlFlow::Throw ) {
		mControlFlow = tmpControlFlow;
	}
}

Runtime::Object* TreeInterpreter::visitTypeDeclaration(TypeDeclaration* node)
{
	Runtime::Object* object = mRepository->createInstance(node->mType, node->mName, node->mConstraints);
	object->setConst(node->mIsConst);
	object->setIsReference(node->mIsReference);

	getScope()->define(node->mName, object);

	if ( node->mAssignment ) {
		tryEvaluteReturnNull(node->mAssignment, object);
	}

	return object;
}

Runtime::Object* TreeInterpreter::visitTypeInference(TypeInference* node)
{
	return visitTypeDeclaration(node);
}

void TreeInterpreter::visitWhile(WhileStatement* node)
{
	Runtime::Object condition;

	for  ( ; ; ) {
		// evaluate while condition
		tryControl(evaluate(node->mCondition, &condition));

		// validate loop condition
		if ( !isTrue(condition) ) {
			break;
		}

		// execute compound statement
		visitStatement(dynamic_cast<Statement*>(node->mStatement));

		// check (and reset) control flow
		switch ( mControlFlow ) {
			case Runtime::ControlFlow::Break: mControlFlow = Runtime::ControlFlow::Normal; return;
			case Runtime::ControlFlow::Continue: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::ExitProgram: mControlFlow = Runtime::ControlFlow::ExitProgram; return;
			case Runtime::ControlFlow::Normal: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::Return: mControlFlow = Runtime::ControlFlow::Return; return;
			case Runtime::ControlFlow::Throw: mControlFlow = Runtime::ControlFlow::Throw; return;
		}
	}
}


}
}
