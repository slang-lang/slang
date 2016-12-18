
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
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Namespace.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeInterpreter::TreeInterpreter()
: mControlFlow(Runtime::ControlFlow::Normal),
  mOwner(0),
  mRepository(0),
  mRootNode(0)
{
	mRepository = Controller::Instance().repository();
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
		case Expression::ExpressionType::LiteralExpression: evaluateLiteral(static_cast<LiteralExpression*>(exp), result); break;
		case Expression::ExpressionType::MethodExpression: evaluateMethodExpression(static_cast<MethodExpression*>(exp), result); break;
		case Expression::ExpressionType::NewExpression: evaluateNewExpression(static_cast<NewExpression*>(exp), result); break;
		case Expression::ExpressionType::UnaryExpression: evaluateUnaryExpression(static_cast<UnaryExpression*>(exp), result); break;
		case Expression::ExpressionType::VariableExpression: evaluateVariable(static_cast<VariableExpression*>(exp), result); break;

		case Expression::ExpressionType::TypecastExpression:
			throw Common::Exceptions::NotSupported("expression type not supported yet");
	}
}

void TreeInterpreter::evaluateBinaryExpression(BinaryExpression* exp, Runtime::Object* result)
{
	if ( exp->getBinaryExpressionType() == BinaryExpression::BinaryExpressionType::BooleanBinaryExpression ) {
		evaluateBooleanBinaryExpression(exp, result);
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
	catch ( Runtime::ControlFlow::E& e ) {
		mControlFlow = e;
		return;
	}

	switch ( exp->mToken.type() ) {
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
		default:
			throw Common::Exceptions::NotSupported("binary expression with " + exp->mToken.content() + " not supported");
		// }
	}

	// assign (left ? right) to result
	Runtime::operator_binary_assign(result, &left);
}

void TreeInterpreter::evaluateBooleanBinaryExpression(BinaryExpression* exp, Runtime::Object* result)
{
	Runtime::Object left;
	Runtime::Object right;

	try {
		// evaluate left expression
		evaluate(exp->mLeft, &left);

		// incomplete boolean evaluation
		if ( exp->mToken.type() == Token::Type::AND && !isTrue(left) ) {
			*result = Runtime::BoolObject(false);
			return;
		}
		else if ( exp->mToken.type() == Token::Type::OR && isTrue(left) ) {
			*result = Runtime::BoolObject(true);
			return;
		}

		// evaluate right expression
		evaluate(exp->mRight, &right);
	}
	catch ( Runtime::ControlFlow::E& e ) {
		mControlFlow = e;
		return;
	}

	switch ( exp->mToken.type() ) {
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

		default:
			throw Common::Exceptions::NotSupported("binary expression with " + exp->mToken.content() + " not supported (by now)");
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

void TreeInterpreter::evaluateNewExpression(NewExpression* exp, Runtime::Object* result)
{
	MethodExpression* method = dynamic_cast<MethodExpression*>(exp->mExpression);
	if ( !method ) {
		throw Runtime::Exceptions::Exception("invalid method expression found");
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
	*result = *mRepository->createReference(static_cast<Designtime::BluePrintGeneric*>(exp->mSymbol), ANONYMOUS_OBJECT, PrototypeConstraints(), Repository::InitilizationType::Final);

	// execute new object's constructor
	mControlFlow = result->Constructor(params);
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
	MethodScope* scope = getEnclosingMethodScope();
	if ( !scope ) {
		throw Runtime::Exceptions::Exception("could not resolve parent scope");
	}

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

	Symbol* symbol = scope->resolveMethod(exp->mName, params, false);
	if ( !symbol ) {
		throw Runtime::Exceptions::Exception("method " + exp->mName + " not found");
	}

	Runtime::Method* method = static_cast<Runtime::Method*>(symbol);
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

void TreeInterpreter::evaluateUnaryExpression(UnaryExpression* exp, Runtime::Object* result)
{
	Runtime::Object left;

	try {
		// evaluate left expression
		evaluate(exp->mExpression, &left);
	}
	catch ( Runtime::ControlFlow::E& e ) {
		mControlFlow = e;
		return;
	}

	switch ( exp->mToken.type() ) {
		// boolean expressions
		// {
		case Token::Type::OPERATOR_NOT: Runtime::operator_unary_not(&left); break;
		// }

		// math expressions
		// {
		case Token::Type::MATH_ADDITION: /* this is empty by intend */ break;
		case Token::Type::MATH_SUBTRACT: Runtime::operator_unary_minus(&left); break;
		case Token::Type::OPERATOR_DECREMENT: Runtime::operator_unary_decrement(&left); break;
		case Token::Type::OPERATOR_INCREMENT: Runtime::operator_unary_increment(&left); break;
		// }

		// default handling
		// {
		default:
			throw Common::Exceptions::NotSupported("binary expression with " + exp->mToken.content() + " not supported (by now)");
		// }
	}

	Runtime::operator_binary_assign(result, &left);
}

void TreeInterpreter::evaluateVariable(VariableExpression* exp, Runtime::Object* result)
{
	Symbol* lvalue = getScope()->resolve(exp->mName.content(), false, Visibility::Designtime);
	if ( !lvalue ) {
		throw Runtime::Exceptions::InvalidAssignment("lvalue '" + exp->mName.content() + "' not found", exp->mName.position());
	}

	if ( lvalue->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Runtime::Exceptions::Exception("invalid lvalue symbol type");
	}

	*result = *static_cast<Runtime::Object*>(lvalue);
}

Runtime::ControlFlow::E TreeInterpreter::execute(Runtime::Method* method, const ParameterList& params, Runtime::Object* result)
{
	(void)result;

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

	Runtime::Method scope(*method);

	IScope* previousOwner = mOwner;

	mOwner = method->getEnclosingScope();

	ParameterList executedParams = method->mergeParameters(params);

	// add parameters as locale variables
	for ( ParameterList::const_iterator it = executedParams.begin(); it != executedParams.end(); ++it ) {
		Runtime::Object *object = 0;

		switch ( it->access() ) {
			case Parameter::AccessMode::ByReference: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				if ( it->reference().isValid() ) {
					object->assign(
						*Controller::Instance().memory()->get(it->reference())
					);
				}

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);

				scope.define(it->name(), object);
			} break;
			case Parameter::AccessMode::ByValue: {
				object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);
				object->setValue(it->value());

				scope.define(it->name(), object);
			} break;
			case Parameter::AccessMode::Unspecified: {
				throw Common::Exceptions::AccessMode("unspecified access mode");
			} break;
		}
	}

	mRootNode = method->getRootNode();

	// record stack
	Controller::Instance().stack()->push(&scope, executedParams);
	// notify debugger
	Core::Debugger::Instance().notifyEnter(&scope, Core::Debugger::immediateBreakToken);
	// interpret scope tokens
	//ControlFlow::E controlflow = interpret(getTokens(), result);
	process(mRootNode);

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

Runtime::Namespace* TreeInterpreter::getEnclosingNamespace(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Runtime::Namespace* result = dynamic_cast<Runtime::Namespace*>(parent);
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

IScope* TreeInterpreter::getScope() const
{
	StackLevel* stack = Controller::Instance().stack()->current();

	return stack->getScope();
}

inline Symbol* TreeInterpreter::identify(TokenIterator& token) const
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
				Runtime::Namespace* space = getEnclosingNamespace(getScope());
				if ( space ) {
					result = getScope()->resolve(space->QualifiedTypename() + "." + identifier, onlyCurrentScope, Visibility::Private);
				}
			}
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::BluePrintEnumSymbol:
					//result = dynamic_cast<Designtime::BluePrintEnum*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::BluePrintObjectSymbol:
					//result = dynamic_cast<Designtime::BluePrintObject*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = dynamic_cast<Runtime::Namespace*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::ObjectSymbol:
					result = dynamic_cast<Runtime::Object*>(result)->resolve(identifier, onlyCurrentScope,
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

Symbol* TreeInterpreter::identifyMethod(TokenIterator& token, const ParameterList& params) const
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
					//result = dynamic_cast<Designtime::BluePrintEnum*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::BluePrintObjectSymbol:
					//result = dynamic_cast<Designtime::BluePrintObject*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = dynamic_cast<Runtime::Namespace*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::ObjectSymbol:
					result = dynamic_cast<Runtime::Object*>(result)->resolveMethod(identifier, params, true,
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

void TreeInterpreter::popScope()
{
	StackLevel* stack = Controller::Instance().stack()->current();

	stack->popScope();
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
				result += " " + bin->mToken.content() + " ";
				result += printExpression(bin->mRight) + ")";
			} break;
			case Expression::ExpressionType::CopyExpression: {
				result += "copy " + printExpression(static_cast<CopyExpression*>(expression)->mExpression);
			} break;
			case Expression::ExpressionType::NewExpression: {
				result += "new " + printExpression(static_cast<NewExpression*>(expression)->mExpression);
			} break;
			case Expression::ExpressionType::LiteralExpression: {
				result += static_cast<LiteralExpression*>(expression)->mValue.toStdString();
			} break;
			case Expression::ExpressionType::MethodExpression: {
				result += static_cast<MethodExpression*>(expression)->mName;
				result += "(";
				for ( ExpressionList::const_iterator it = static_cast<MethodExpression*>(expression)->mParams.begin(); it != static_cast<MethodExpression*>(expression)->mParams.end(); ++it ) {
					result += printExpression((*it));
				}
				result += ")";
			} break;
			case Expression::ExpressionType::TypecastExpression: {
				result += static_cast<TypecastExpression*>(expression)->mDestinationType + " ";
				result += printExpression(static_cast<TypecastExpression*>(expression)->mExpression);
			} break;
			case Expression::ExpressionType::UnaryExpression: {
				UnaryExpression* bin = static_cast<UnaryExpression*>(expression);

				result += bin->mToken.content();
				result += printExpression(bin->mExpression);
			} break;
			case Expression::ExpressionType::VariableExpression: {
				result += static_cast<VariableExpression*>(expression)->mName.content();
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
	StackLevel* stack = Controller::Instance().stack()->current();

	bool allowDelete = !scope;

	if ( !scope ) {
		scope = new SymbolScope(stack->getScope());
	}

	stack->pushScope(scope, allowDelete);
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
	Symbol* lvalue = getScope()->resolve(node->mName.content(), false, Visibility::Designtime);
	if ( !lvalue ) {
		throw Runtime::Exceptions::InvalidAssignment("lvalue '" + node->mName.content() + "' not found");
	}

	if ( lvalue->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Runtime::Exceptions::Exception("invalid lvalue symbol type");
	}

	evaluate(node->mExpression, static_cast<Runtime::Object*>(lvalue));
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

	Controller::Instance().memory()->remove(obj.getReference());
}

void TreeInterpreter::visitExit(ExitStatement* /*node*/)
{
	throw Runtime::ControlFlow::ExitProgram;
}

void TreeInterpreter::visitExpression(Expression *expression)
{
	//std::cout << printExpression(expression) << ";" << std::endl;

	Runtime::Object tmp;
	evaluate(expression, &tmp);
}

void TreeInterpreter::visitFor(ForStatement* node)
{
	// execute initialization statement
	visitStatement(static_cast<Statement*>(node->mInitialization));

	// reset control flow to normal
	mControlFlow = Runtime::ControlFlow::Normal;

	Runtime::Object condition;

	for  ( ; ; ) {
		try {
			// evaluate loop condition
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
		visit(node->mStatement);

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

void TreeInterpreter::visitForeach(ForeachStatement *node)
{
	std::cout << "for ( ";

	visitStatement(node->mTypeDeclaration);

	std::cout << " : " << node->mLoopVariable.content() << " ) ";

	visit(node->mStatement);
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
		visit(node->mIfBlock);
	}
	else { // execute else-compound statement
		visit(node->mElseBlock);
	}
}

void TreeInterpreter::visitOperator(Operator* /*op*/)
{
	std::cout << "Operator" << std::endl;
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
	std::cout << "return " << printExpression(node->mExpression) << ";" << std::endl;

	mControlFlow = Runtime::ControlFlow::Return;
}

void TreeInterpreter::visitStatement(Statement *node)
{
	Core::Debugger::Instance().notify(getScope(), Token());		// notify debugger

	assert(node);

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
	pushScope();

	process(node);

	popScope();
}

void TreeInterpreter::visitSwitch(SwitchStatement* node)
{
	Runtime::Object value;
	try {
		evaluate(node->mExpression, &value);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	bool caseMatched = false;

	for ( CaseStatements::const_iterator it = node->mCaseStatements.begin(); it != node->mCaseStatements.end(); ++it ) {
		Runtime::Object caseValue;
		try {
			evaluate((*it)->mCaseExpression, &caseValue);
		}
		catch ( Runtime::ControlFlow::E &e ) {
			mControlFlow = e;
			return;
		}

		if ( Runtime::operator_binary_equal(&value, &caseValue) ) {
			visit((*it)->mCaseBlock);

			switch ( mControlFlow ) {
				case Runtime::ControlFlow::Break:
					mControlFlow = Runtime::ControlFlow::Normal;
					return;	// stop matching the remaining case-statements
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

	// no matching case statement found => execute default statement
	if ( !caseMatched ) {
		visit(node->mDefaultStatement);
	}
}

void TreeInterpreter::visitThrow(ThrowStatement* node)
{
	Runtime::Object* data = mRepository->createInstance(OBJECT, ANONYMOUS_OBJECT, PrototypeConstraints());
	try {
		evaluate(node->mExpression, data);
	}
	catch ( Runtime::ControlFlow::E &e ) {
		mControlFlow = e;
		return;
	}

	mControlFlow = Runtime::ControlFlow::Throw;
	Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, Common::Position());

	// notify our debugger that an exception has been thrown
	Core::Debugger::Instance().notifyExceptionThrow(getScope(), Token());
}

void TreeInterpreter::visitTry(TryStatement* node)
{
	// execute try-block
	visitStatement(node->mTryBlock);

	// execute exception handling only if an exception occurred
	if ( mControlFlow == Runtime::ControlFlow::Throw && !node->mCatchStatements.empty() ) {
		// get exception data
		Runtime::Object* exception = Controller::Instance().stack()->exception().getData();

		// determine correct catch-block (if a correct one exists)
		for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
			Designtime::BluePrintGeneric* catchType = static_cast<Designtime::BluePrintGeneric*>((*it)->mTypeDeclaration->mSymbol);

			if ( exception->isInstanceOf(catchType->QualifiedTypename()) ) {
				mControlFlow = Runtime::ControlFlow::Normal;

				pushScope();
					visit((*it)->mTypeDeclaration);

					visit((*it)->mStatement);
				popScope();

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
		visitStatement(node->mFinallyBlock);
	}

	// reset control flow if finally block has been executed normally
	if ( mControlFlow == Runtime::ControlFlow::Normal ) {
		mControlFlow = tmpControlFlow;
	}
}

void TreeInterpreter::visitTypeDeclaration(TypeDeclaration* node)
{
	Runtime::Object* object = mRepository->createInstance(static_cast<Designtime::BluePrintGeneric*>(node->mSymbol), node->mName, node->mConstraints);

	getScope()->define(node->mName, object);

	if ( node->mAssignment ) {
		evaluate(node->mAssignment, object);
	}
}

void TreeInterpreter::visitWhile(WhileStatement* node)
{
	// reset control flow to normal
	mControlFlow = Runtime::ControlFlow::Normal;

	Runtime::Object condition;

	for  ( ; ; ) {
		try {
			// evaluate while condition
			evaluate(node->mExpression, &condition);
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
		visit(node->mStatements);

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
