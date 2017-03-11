
// Header
#include "TreeInterpreter.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/GenericObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Utils.h>
#include <Core/Designtime/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeInterpreter::TreeInterpreter()
: mControlFlow(Runtime::ControlFlow::Normal),
  mOwner(0)
{
	// initialize virtual machine stuff
	mDebugger = &Core::Debugger::Instance();
	mMemory = Controller::Instance().memory();
	mRepository = Controller::Instance().repository();
	mStack = Controller::Instance().stack();
}

TreeInterpreter::~TreeInterpreter()
{
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
		case Expression::ExpressionType::SymbolExpression: evaluateSymbol(static_cast<SymbolExpression *>(exp), result, getScope()); break;
		case Expression::ExpressionType::TypecastExpression: evaluateTypeCastExpression(static_cast<TypecastExpression*>(exp), result); break;
		case Expression::ExpressionType::TypeidExpression: evaluateTypeidExpression(static_cast<TypeidExpression*>(exp), result); break;
		case Expression::ExpressionType::UnaryExpression: evaluateUnaryExpression(static_cast<UnaryExpression*>(exp), result); break;
	}
}

void TreeInterpreter::evaluateBinaryExpression(BinaryExpression* exp, Runtime::Object* result)
{
	if ( exp->getBinaryExpressionType() == BinaryExpression::BinaryExpressionType::BooleanBinaryExpression ) {
		evaluateBooleanBinaryExpression(static_cast<BooleanBinaryExpression*>(exp), result);
		return;
	}

	Runtime::Object left;
	Runtime::Object right;

	try {
		// evaluate left expression
		evaluate(exp->mLeft, &left);

		// evaluate right expression
		evaluate(exp->mRight, &right);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

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
	Runtime::Object right;

	try {
		// evaluate left expression
		evaluate(exp->mLeft, &left);

		// incomplete boolean evaluation
		if ( exp->mOperation.type() == Token::Type::AND && !isTrue(left) ) {
			*result = Runtime::BoolObject(false);
			return;
		}
		else if ( exp->mOperation.type() == Token::Type::OR && isTrue(left) ) {
			*result = Runtime::BoolObject(true);
			return;
		}

		// evaluate right expression
		evaluate(exp->mRight, &right);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	switch ( exp->mOperation.type() ) {
		// boolean expressions
		// {
		case Token::Type::AND: *result = Runtime::BoolObject(isTrue(left) && isTrue(right)); break;
		case Token::Type::NAND: *result = Runtime::BoolObject(!isTrue(left) && !isTrue(right)); break;
		case Token::Type::NOR: *result = Runtime::BoolObject(!isTrue(left) || !isTrue(right)); break;
		case Token::Type::OR: *result = Runtime::BoolObject(isTrue(left) || isTrue(right)); break;
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
		default: throw Common::Exceptions::NotSupported("binary expression with " + exp->mOperation.content() + " not supported (by now)");
		// }
	}
}

void TreeInterpreter::evaluateCopyExpression(CopyExpression* exp, Runtime::Object* result)
{
	Runtime::Object obj;
	try {
		evaluate(exp->mExpression, &obj);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	result->copy(obj);
}

void TreeInterpreter::evaluateIsExpression(IsExpression* exp, Runtime::Object* result)
{
	Runtime::Object tmp;
	try {
		// evaluate left expression
		evaluate(exp->mExpression, &tmp);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	*result = Runtime::BoolObject(tmp.isInstanceOf(exp->mMatchType));
}

void TreeInterpreter::evaluateLiteral(LiteralExpression* exp, Runtime::Object* result)
{
	switch ( exp->mValue.type() ) {
		case Runtime::AtomicValue::Type::BOOL: *result = Runtime::BoolObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::DOUBLE: *result = Runtime::DoubleObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::FLOAT: *result = Runtime::FloatObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::INT: *result = Runtime::IntegerObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::STRING: *result = Runtime::StringObject(exp->mValue); break;
		case Runtime::AtomicValue::Type::UINT: throw Common::Exceptions::NotSupported("UINT type");
		case Runtime::AtomicValue::Type::UNKOWN: throw Common::Exceptions::NotSupported("UNKNOWN type");
	}
}

void TreeInterpreter::evaluateMethodExpression(MethodExpression* exp, Runtime::Object* result)
{
	std::list<Runtime::Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	for ( ExpressionList::const_iterator it = exp->mParams.begin(); it != exp->mParams.end(); ++it ) {
		objectList.push_back(Runtime::Object());

		Runtime::Object* param = &objectList.back();

		try {
			evaluate((*it), param);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		params.push_back(Parameter::CreateRuntime(param->QualifiedOuterface(), param->getValue(), param->getReference()));
	}

	MethodSymbol* methodSymbol = resolveMethod(getScope(), exp->mSymbol, params, false, Visibility::Private);
	if ( !methodSymbol ) {
		methodSymbol = resolveMethod(getEnclosingMethodScope(), exp->mSymbol, params, false, Visibility::Private);
	}
	if ( !methodSymbol ) {
		throw Runtime::Exceptions::RuntimeException("method " + exp->mSymbol->toString() + " not found");
	}

	Common::Method* method = static_cast<Common::Method*>(methodSymbol);
	assert(method);

	Runtime::ControlFlow::E controlflow;

	if ( method->isExtensionMethod() ) {
		controlflow = method->execute(params, result, Token());
	}
	else {
		controlflow = execute(method, params, result);
	}

	switch ( controlflow ) {
		case Runtime::ControlFlow::ExitProgram:
			mControlFlow = Runtime::ControlFlow::ExitProgram;
			break;
		case Runtime::ControlFlow::Throw:
			mControlFlow = Runtime::ControlFlow::Throw;
			throw Runtime::ControlFlow::Throw;			// throw even further
		default:
			mControlFlow = Runtime::ControlFlow::Normal;
			break;
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
		objectList.push_back(Runtime::Object());

		Runtime::Object* param = &objectList.back();
		try {
			evaluate((*it), param);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		params.push_back(Parameter::CreateRuntime(param->QualifiedOuterface(), param->getValue(), param->getReference()));
	}

	// create initialized reference of new object
	*result = *mRepository->createReference(exp->mType, ANONYMOUS_OBJECT, PrototypeConstraints(), Repository::InitilizationType::Final);

	// execute new object's constructor
	mControlFlow = result->Constructor(params);
}

void TreeInterpreter::evaluateSymbol(SymbolExpression* exp, Runtime::Object* result, IScope* scope)
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
			case Symbol::IType::BluePrintEnumSymbol:
				scope = static_cast<Designtime::BluePrintEnum*>(lvalue);
				break;
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

		evaluateSymbol(exp->mSymbolExpression, result, scope);
		return;
	}

	if ( lvalue->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Runtime::Exceptions::RuntimeException("invalid lvalue symbol type");
	}

	*result = *static_cast<Runtime::Object*>(lvalue);
}

void TreeInterpreter::evaluateTypeCastExpression(TypecastExpression* exp, Runtime::Object* result)
{
	Runtime::Object tmp;

	try {
		evaluate(exp->mExpression, &tmp);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	Runtime::typecast(&tmp, exp->mDestinationType);

	Runtime::operator_binary_assign(result, &tmp);
}

void TreeInterpreter::evaluateTypeidExpression(TypeidExpression* exp, Runtime::Object* result)
{
	Runtime::Object tmp;
	try {
		evaluate(exp->mExpression, &tmp);

		Runtime::StringObject type(tmp.QualifiedTypename());
		Runtime::operator_binary_assign(result, &type);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}
}

void TreeInterpreter::evaluateUnaryExpression(UnaryExpression* exp, Runtime::Object* result)
{
	try {
		evaluate(exp->mExpression, result);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	switch ( exp->mOperation.type() ) {
		// boolean expressions
		// {
		case Token::Type::OPERATOR_NOT: Runtime::operator_unary_not(result); break;
		// }

		// math expressions
		// {
		case Token::Type::MATH_ADDITION: /* this is empty by intend */ break;
		case Token::Type::MATH_SUBTRACT: Runtime::operator_unary_minus(result); break;
		case Token::Type::OPERATOR_DECREMENT: Runtime::operator_unary_decrement(result); break;
		case Token::Type::OPERATOR_INCREMENT: Runtime::operator_unary_increment(result); break;
		// }

		// default handling
		// {
		default: throw Common::Exceptions::NotSupported("expression with " + exp->mOperation.content() + " not supported (by now)");
		// }
	}
}

Runtime::ControlFlow::E TreeInterpreter::execute(Common::Method* method, const ParameterList& params, Runtime::Object* result)
{
	if ( method->isAbstract() ) {
		throw Common::Exceptions::AbstractException("cannot execute abstract method '" + method->getFullScopeName() + "'");
	}
	if ( !method->isSignatureValid(params) ) {
		throw Common::Exceptions::ParameterCountMissmatch("incorrect number or type of parameters");
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
		Runtime::Object *object = 0;

		switch ( it->access() ) {
			case AccessMode::ByReference: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				if ( it->reference().isValid() ) {
					object->assign(
						*mMemory->get(it->reference())
					);
				}

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);

				scope.define(it->name(), object);
			} break;
			case AccessMode::ByValue: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);
				object->setValue(it->value());

				scope.define(it->name(), object);
			} break;
			case AccessMode::Unspecified: {
				throw Common::Exceptions::AccessMode("unspecified access mode");
			} break;
		}
	}

	// record stack
	mStack->push(&scope, TokenList(), executedParams);

	// notify debugger
	mDebugger->notifyEnter(&scope, Core::Debugger::immediateBreakToken);

	// interpret scope tokens
	process(method->getRootNode());

	// notify debugger
	mDebugger->notifyExit(&scope, Core::Debugger::immediateBreakToken);

	mOwner = previousOwner;

	if ( result ) {
		*result = mStack->current()->returnValue();
	}

	// unwind stack
	mStack->pop();

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

void TreeInterpreter::popScope()
{
	mStack->current()->popScope();
}

std::string TreeInterpreter::printExpression(Node* node) const
{
	std::string result;

	if ( node ) {
		assert(node->getNodeType() == Node::NodeType::Expression);
		Expression* expression = static_cast<Expression*>(node);

		switch ( expression->getExpressionType() ) {
			case Expression::ExpressionType::BinaryExpression: {
				BinaryExpression* bin = static_cast<BinaryExpression*>(node);

				result += "(" + printExpression(bin->mLeft);
				result += " " + bin->mOperation.content() + " ";
				result += printExpression(bin->mRight) + ")";
			} break;
			case Expression::ExpressionType::CopyExpression: {
				result += "copy " + printExpression(static_cast<CopyExpression*>(expression)->mExpression);
			} break;
			case Expression::ExpressionType::IsExpression: {
				result += printExpression(static_cast<IsExpression*>(expression)->mExpression) + " is " + static_cast<IsExpression*>(expression)->mMatchType;
			} break;
			case Expression::ExpressionType::NewExpression: {
				result += "new " + printExpression(static_cast<NewExpression*>(expression)->mExpression);
			} break;
			case Expression::ExpressionType::LiteralExpression: {
				result += static_cast<LiteralExpression*>(expression)->mValue.toStdString();
			} break;
			case Expression::ExpressionType::MethodExpression: {
				result += printExpression(static_cast<MethodExpression*>(expression)->mSymbol);
				result += "(";
				for ( ExpressionList::const_iterator it = static_cast<MethodExpression*>(expression)->mParams.begin(); it != static_cast<MethodExpression*>(expression)->mParams.end(); ++it ) {
					result += printExpression((*it));
				}
				result += ")";
			} break;
			case Expression::ExpressionType::SymbolExpression: {
				if ( static_cast<SymbolExpression*>(expression)->mSymbolExpression ) {
					result += printExpression(static_cast<SymbolExpression*>(expression)->mSymbolExpression);
				}
				else {
					result += static_cast<SymbolExpression*>(expression)->mName;
				}
			} break;
			case Expression::ExpressionType::TypecastExpression: {
				result += static_cast<TypecastExpression*>(expression)->mDestinationType + " ";
				result += printExpression(static_cast<TypecastExpression*>(expression)->mExpression);
			} break;
			case Expression::ExpressionType::TypeidExpression: {
				result += "typeid(" + printExpression(static_cast<TypeidExpression*>(expression)->mExpression) + ")";
			} break;
			case Expression::ExpressionType::UnaryExpression: {
				UnaryExpression* bin = static_cast<UnaryExpression*>(expression);

				result += bin->mOperation.content();
				result += printExpression(bin->mExpression);
			} break;
		}
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

	if ( !scope ) {
		scope = new SymbolScope(stack->getScope());
	}

	stack->pushScope(scope, allowDelete, true);
}

Symbol* TreeInterpreter::resolve(IScope* scope, SymbolExpression* symbol, bool onlyCurrentScope, Visibility::E visibility) const
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
			case Symbol::IType::NamespaceSymbol:
				scope = static_cast<Common::Namespace*>(child);
				break;
			case Symbol::IType::BluePrintEnumSymbol:
			case Symbol::IType::BluePrintObjectSymbol:
				scope = static_cast<Designtime::BluePrintObject*>(child);
				break;
			case Symbol::IType::ObjectSymbol:
				scope = static_cast<Runtime::Object*>(child);
				break;
			case Symbol::IType::MethodSymbol:
				throw Designtime::Exceptions::DesigntimeException("invalid symbol type found");
		}

		symbol = symbol->mSymbolExpression;
	}

	return scope->resolve(symbol->mName, onlyCurrentScope, visibility);
}

MethodSymbol* TreeInterpreter::resolveMethod(IScope* scope, SymbolExpression* symbol, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const
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
			case Symbol::IType::BluePrintEnumSymbol:
			case Symbol::IType::MethodSymbol:
				throw Designtime::Exceptions::DesigntimeException("invalid symbol type found");
		}

		symbol = symbol->mSymbolExpression;
	}

	MethodScope* methodScope = dynamic_cast<MethodScope*>(scope);
	if ( !methodScope ) {
		return 0;
	}

	return methodScope->resolveMethod(symbol->mName, params, onlyCurrentScope, visibility);
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

	try {
		evaluate(node->mExpression, &condition);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	if ( !isTrue(condition) ) {
		std::cout << "assert(" << printExpression(node->mExpression) << ");" << std::endl;

		throw Runtime::Exceptions::AssertionFailed(condition.ToString(), node->mPosition);
	}
}

void TreeInterpreter::visitAssignment(Assignment* node)
{
	IScope* scope = getScope();

	Symbol* lvalue = scope->resolve(node->mLValue->mName, false, Visibility::Designtime);
	if ( !lvalue ) {
		throw Runtime::Exceptions::InvalidAssignment("lvalue '" + node->mLValue->mName + "' not found");
	}

	if ( lvalue->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Runtime::Exceptions::RuntimeException("invalid lvalue symbol type");
	}

	Runtime::Object tmp;
	try {
		evaluate(node->mExpression, &tmp);

		Runtime::operator_binary_assign(static_cast<Runtime::Object*>(lvalue), &tmp);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}
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

	try {
		evaluate(node->mExpression, &obj);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	obj = Runtime::Object();
}

void TreeInterpreter::visitExit(ExitStatement* node)
{
	Runtime::Object* data = mRepository->createInstance(Runtime::IntegerObject::TYPENAME, ANONYMOUS_OBJECT, PrototypeConstraints());

	try {
		evaluate(node->mExpression, data);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	mStack->exception() = Runtime::ExceptionData(data, Common::Position());

	throw Runtime::ControlFlow::ExitProgram;
}

void TreeInterpreter::visitExpression(Expression* expression)
{
	Runtime::Object tmp;

	try {
		evaluate(expression, &tmp);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}
}

void TreeInterpreter::visitFor(ForStatement* node)
{
	// execute initialization statement
	visitStatement(static_cast<Statement*>(node->mInitialization));

	Runtime::Object condition;

	for  ( ; ; ) {
		try {
			evaluate(node->mCondition, &condition);		// evaluate loop condition
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		// validate loop condition
		if ( !isTrue(condition) ) {
			break;
		}

		// execute compound statement
		visitStatement(static_cast<Statement*>(node->mStatement));

		// check (and reset) control flow
		switch ( mControlFlow ) {
			case Runtime::ControlFlow::Break: mControlFlow = Runtime::ControlFlow::Normal; return;
			case Runtime::ControlFlow::Continue: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::ExitProgram: mControlFlow = Runtime::ControlFlow::ExitProgram; return;
			case Runtime::ControlFlow::Normal: mControlFlow = Runtime::ControlFlow::Normal; break;
			case Runtime::ControlFlow::Return: mControlFlow = Runtime::ControlFlow::Return; return;
			case Runtime::ControlFlow::Throw: mControlFlow = Runtime::ControlFlow::Throw; return;
		}

		visitStatement(static_cast<Statement*>(node->mIteration));
	}
}

void TreeInterpreter::visitForeach(ForeachStatement* node)
{
	//IScope* scope = getScope();

	Runtime::Object collection;
	evaluate(node->mLoopVariable, &collection);

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
		visitStatement(static_cast<Statement*>(node->mStatement));

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
	Runtime::Object condition;

	try {
		// evaluate if-condition
		evaluate(node->mExpression, &condition);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	// validate if-condition
	if ( isTrue(condition) ) { // execute if-compound statement
		visitStatement(static_cast<Statement*>(node->mIfBlock));
	}
	else { // execute else-compound statement
		visitStatement(static_cast<Statement*>(node->mElseBlock));
	}
}

void TreeInterpreter::visitOperator(Operator* /*op*/)
{
	throw Common::Exceptions::SyntaxError("cannot process standalone operator");
}

void TreeInterpreter::visitPrint(PrintStatement* node)
{
	Runtime::Object text;
	try {
		evaluate(node->mExpression, &text);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	::Utils::PrinterDriver::Instance()->print(text.getValue().toStdString(), node->mPosition.mFile, node->mPosition.mLine);
}

void TreeInterpreter::visitReturn(ReturnStatement* node)
{
	if ( node->mExpression ) {	// only process not-empty return statements
		Runtime::Object tmp;
		try {
			evaluate(node->mExpression, &tmp);

			Runtime::operator_binary_assign(&mStack->current()->returnValue(), &tmp);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}
	}

	mControlFlow = Runtime::ControlFlow::Return;
}

void TreeInterpreter::visitStatement(Statement *node)
{
	if ( !node ) {
		return;
	}

	mDebugger->notify(getScope(), Token());		// notify debugger

	switch ( node->getStatementType() ) {
		case Statement::StatementType::AssertStatement:
			visitAssert(static_cast<AssertStatement*>(node));
			break;
		case Statement::StatementType::Assignment:
			visitAssignment(static_cast<Assignment*>(node));
			break;
		case Statement::StatementType::BreakStatement:
			visitBreak(static_cast<BreakStatement*>(node));
			break;
		case Statement::StatementType::CaseStatement:
			throw Common::Exceptions::Exception("case statements are handled separately!");
		case Statement::StatementType::CatchStatement:
			throw Common::Exceptions::Exception("catch statements are handled separately!");
		case Statement::StatementType::ContinueStatement:
			visitContinue(static_cast<ContinueStatement*>(node));
			break;
		case Statement::StatementType::DeleteStatement:
			visitDelete(static_cast<DeleteStatement*>(node));
			break;
		case Statement::StatementType::ExitStatement:
			visitExit(static_cast<ExitStatement*>(node));
			break;
		case Statement::StatementType::ForeachStatement:
			visitForeach(static_cast<ForeachStatement *>(node));
			break;
		case Statement::StatementType::ForStatement:
			visitFor(static_cast<ForStatement*>(node));
			break;
		case Statement::StatementType::IfStatement:
			visitIf(static_cast<IfStatement*>(node));
			break;
		case Statement::StatementType::PrintStatement:
			visitPrint(static_cast<PrintStatement*>(node));
			break;
		case Statement::StatementType::ReturnStatement:
			visitReturn(static_cast<ReturnStatement*>(node));
			break;
		case Statement::StatementType::Statements:
			visitStatements(static_cast<Statements*>(node));
			break;
		case Statement::StatementType::SwitchStatement:
			visitSwitch(static_cast<SwitchStatement*>(node));
			break;
		case Statement::StatementType::ThrowStatement:
			visitThrow(static_cast<ThrowStatement*>(node));
			break;
		case Statement::StatementType::TryStatement:
			visitTry(static_cast<TryStatement*>(node));
			break;
		case Statement::StatementType::TypeDeclaration:
			visitTypeDeclaration(static_cast<TypeDeclaration*>(node));
			break;
		case Statement::StatementType::WhileStatement:
			visitWhile(static_cast<WhileStatement*>(node));
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
	bool caseMatched = false;
	bool evaluateCaseExpression = true;
	Runtime::Object value;

	for ( CaseStatements::const_iterator it = node->mCaseStatements.begin(); it != node->mCaseStatements.end(); ++it ) {
		if ( evaluateCaseExpression ) {
			try {
				evaluate(node->mExpression, &value);

				evaluateCaseExpression = false;
			}
			catch ( Runtime::ControlFlow::E &e ) {
				mControlFlow = e;
				return;
			}
		}

		Runtime::Object caseValue;
		try {
			evaluate((*it)->mCaseExpression, &caseValue);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		if ( Runtime::operator_binary_equal(&value, &caseValue) ) {
			caseMatched = true;

			visitStatements((*it)->mCaseBlock);

			switch ( mControlFlow ) {
				case Runtime::ControlFlow::Break:
					mControlFlow = Runtime::ControlFlow::Normal;
					return;	// stop matching the remaining case-statements
				case Runtime::ControlFlow::Continue:
					mControlFlow = Runtime::ControlFlow::Normal;
					evaluateCaseExpression = true;
					break;	// continue matching the remaining case-statements
				case Runtime::ControlFlow::Normal:
					mControlFlow = Runtime::ControlFlow::Normal;
					return;	// stop matching the remaining case-statements
				case Runtime::ControlFlow::ExitProgram:
				case Runtime::ControlFlow::Return:
				case Runtime::ControlFlow::Throw:
					return;	// no further processing, keep current control flow state
			}
		}
	}

	// no matching case statement found => execute default statement
	if ( !caseMatched ) {
		visitStatements(node->mDefaultStatement);

		switch ( mControlFlow ) {
			case Runtime::ControlFlow::Break:
			case Runtime::ControlFlow::Continue:
			case Runtime::ControlFlow::Normal:
				mControlFlow = Runtime::ControlFlow::Normal;
				break;	// continue matching the remaining case-statements
			case Runtime::ControlFlow::ExitProgram:
			case Runtime::ControlFlow::Return:
			case Runtime::ControlFlow::Throw:
				return;	// no further processing, keep current control flow state
		}
	}
}

void TreeInterpreter::visitThrow(ThrowStatement* node)
{
	Runtime::Object* data = mRepository->createInstance(OBJECT, ANONYMOUS_OBJECT, PrototypeConstraints());

	if ( node->mExpression ) {	// throw new expression
		try {
			evaluate(node->mExpression, data);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		mStack->exception() = Runtime::ExceptionData(data, Common::Position());
	}

	mControlFlow = Runtime::ControlFlow::Throw;

	// notify our debugger that an exception has been thrown
	mDebugger->notifyExceptionThrow(getScope(), Token());
}

void TreeInterpreter::visitTry(TryStatement* node)
{
	// execute try-block
	visitStatements(node->mTryBlock);

	// execute exception handling only if an exception occurred
	if ( mControlFlow == Runtime::ControlFlow::Throw && !node->mCatchStatements.empty() ) {
		// get exception data
		Runtime::Object* exception = mStack->exception().getData();

		// determine correct catch-block (if a correct one exists)
		for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
			if ( exception->isInstanceOf((*it)->mTypeDeclaration->mType) ) {
				// reset control flow to normal to allow execution of catch-block
				mControlFlow = Runtime::ControlFlow::Normal;

				// retrieve exception instance variable
				Runtime::Object* symbol = visitTypeDeclaration((*it)->mTypeDeclaration);

				// assign exception to instance variable
				Runtime::operator_binary_assign(symbol, exception);

				// execute catch statements
				visitStatements((*it)->mStatements);

				// only process one catch-block
				break;
			}
		}
	}

	// store current control flow and reset it after finally block has been executed
	Runtime::ControlFlow::E tmpControlFlow = mControlFlow;

	// reset current control flow to allow execution of finally-block (if one exists)
	mControlFlow = Runtime::ControlFlow::Normal;

	// allow try-statements without finally-statements
	if ( node->mFinallyBlock ) {
		visitStatements(node->mFinallyBlock);
	}

	// reset control flow if finally block has been executed normally
	if ( mControlFlow == Runtime::ControlFlow::Normal ) {
		mControlFlow = tmpControlFlow;
	}
}

Runtime::Object* TreeInterpreter::visitTypeDeclaration(TypeDeclaration* node)
{
	Runtime::Object* object = mRepository->createInstance(node->mType, node->mName, node->mConstraints);

	getScope()->define(node->mName, object);

	object->setConst(node->mIsConst);

	if ( node->mAssignment ) {
		Runtime::Object tmp;
		try {
			evaluate(node->mAssignment, &tmp);

			Runtime::operator_binary_assign(object, &tmp);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return 0;
		}
	}

	return object;
}

void TreeInterpreter::visitWhile(WhileStatement* node)
{
	Runtime::Object condition;

	for  ( ; ; ) {
		try {
			// evaluate while condition
			evaluate(node->mCondition, &condition);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		// validate loop condition
		if ( !isTrue(condition) ) {
			break;
		}

		// execute compound statement
		visitStatement(static_cast<Statement*>(node->mStatement));

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
