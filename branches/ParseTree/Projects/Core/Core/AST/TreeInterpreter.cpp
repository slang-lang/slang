
// Header
#include "TreeInterpreter.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Method.h>
#include <Core/Runtime/Namespace.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/Repository.h>
#include <Debugger/Debugger.h>
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

Runtime::ControlFlow::E TreeInterpreter::execute(Runtime::Method* method, const ParameterList& params, Runtime::Object* result)
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

	// reset qualified typename if prototype constraints are present
	if ( !method->getPrototypeConstraints().empty() ) {
		method->setQualifiedTypename(Designtime::Parser::buildConstraintTypename(method->QualifiedTypename(), method->getPrototypeConstraints()));
		method->setPrototypeConstraints(PrototypeConstraints());
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

NamedScope* TreeInterpreter::getEnclosingMethodScope(IScope* scope) const
{
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
				result += static_cast<VariableExpression*>(expression)->mName;
			} break;
		}
	}

	return result;
}

void TreeInterpreter::process(Statements* statements)
{
	std::cout << "{" << std::endl;

	if ( statements ) {
		for ( Statements::Nodes::const_iterator it = statements->mNodes.begin(); it != statements->mNodes.end(); ++it ) {
			visit((*it));
		}
	}

	std::cout << "}" << std::endl;
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
	if ( node ) {
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
}

void TreeInterpreter::visitAssert(AssertStatement* node)
{
	std::cout << "assert(" << printExpression(node->mExpression) << ");" << std::endl;
}

void TreeInterpreter::visitAssignment(Assignment* node)
{
	std::cout << node->mName.content() << " " << node->mAssignment.content() << " " << printExpression(node->mExpression) << ";" << std::endl;
}

void TreeInterpreter::visitBreak(BreakStatement* /*node*/)
{
	std::cout << "break;" << std::endl;
}

void TreeInterpreter::visitContinue(ContinueStatement* /*node*/)
{
	std::cout << "continue;" << std::endl;
}

void TreeInterpreter::visitDelete(DeleteStatement* node)
{
	std::cout << "delete " << printExpression(node->mExpression) << ";" << std::endl;
}

void TreeInterpreter::visitExit(ExitStatement* node)
{
	std::cout << "exit( " << printExpression(node->mExpression) << " );" << std::endl;
}

void TreeInterpreter::visitExpression(Expression *expression)
{
	std::cout << printExpression(expression) << ";" << std::endl;
}

void TreeInterpreter::visitFor(ForStatement* node)
{
	std::cout << "for ( ";

	visitStatement(static_cast<Statement*>(node->mInitialization));

	std::cout << printExpression(node->mCondition) << "; " << std::endl;

	visitStatement(static_cast<Statement*>(node->mIteration));

	std::cout << ") ";

	visit(node->mLoopBlock);
}

void TreeInterpreter::visitForeach(ForeachStatement *node)
{
	std::cout << "for ( ";

	visitStatement(node->mTypeDeclaration);

	std::cout << " : " << node->mLoopVariable.content() << " ) ";

	visit(node->mLoopBlock);
}

void TreeInterpreter::visitIf(IfStatement* node)
{
	std::cout << "if ( " << printExpression(node->mExpression) << " ) ";

	visit(node->mIfBlock);

	if ( node->mElseBlock && static_cast<Statements*>(node->mElseBlock)->mNodes.size() > 0 ) {
		std::cout << "else ";

		visit(node->mElseBlock);
	}
}

void TreeInterpreter::visitOperator(Operator* /*op*/)
{
	std::cout << "Operator" << std::endl;
}

void TreeInterpreter::visitPrint(PrintStatement* node)
{
	std::cout << "print(" << printExpression(node->mExpression) << ");" << std::endl;
}

void TreeInterpreter::visitReturn(ReturnStatement* node)
{
	std::cout << "return " << printExpression(node->mExpression) << ";" << std::endl;
}

void TreeInterpreter::visitStatement(Statement *node)
{
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
			process(static_cast<Statements*>(node));
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

void TreeInterpreter::visitThrow(ThrowStatement* node)
{
	std::cout << "throw " << printExpression(node->mExpression) << ";" << std::endl;
}

void TreeInterpreter::visitTry(TryStatement* node)
{
	std::cout << "try ";

	visitStatement(node->mTryBlock);

	if ( node->mFinallyBlock ) {
		std::cout << "finally ";

		visitStatement(node->mFinallyBlock);
	}
}

void TreeInterpreter::visitTypeDeclaration(TypeDeclaration* node)
{
	std::cout << node->mType << " " << node->mName;

	if ( node->mAssignment ) {
		std::cout << " = " << printExpression(node->mAssignment) << ";" << std::endl;
	}

/*
	Runtime::Object* object = mRepository->createInstance(static_cast<Designtime::BluePrintGeneric*>(symbol), name, constraints);

	getScope()->define(name, object);
*/
}

void TreeInterpreter::visitWhile(WhileStatement* node)
{
	std::cout << "while ( " << printExpression(node->mExpression) << " ) ";

	visit(node->mStatements);
}


}
}
