
// Header
#include "TreeVisitor.h"

// Library includes
#include <iostream>
#include <Core/Common/Exceptions.h>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeVisitor::TreeVisitor()
{
}

TreeVisitor::~TreeVisitor()
{
}

void TreeVisitor::visit(Node* node)
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

void TreeVisitor::visitAssert(AssertStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitBreak(BreakStatement*)
{
}

void TreeVisitor::visitContinue(ContinueStatement*)
{
}

void TreeVisitor::visitDelete(DeleteStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitExit(ExitStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitExpression(Expression* expression)
{
	if ( !expression ) {
		return;
	}

	assert(expression->getNodeType() == Node::NodeType::Expression);

	switch ( expression->getExpressionType() ) {
		case Expression::ExpressionType::AssignmentExpression: {
			AssignmentExpression* ass = static_cast<AssignmentExpression*>(expression);

			visit(ass->mLHS);
			visit(ass->mRHS);
		} break;
		case Expression::ExpressionType::BinaryExpression: {
			BinaryExpression* bin = static_cast<BinaryExpression*>(expression);

			visit(bin->mLHS);
			visit(bin->mRHS);
		} break;
		case Expression::ExpressionType::CopyExpression: {
			visit(static_cast<CopyExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::IsExpression: {
			IsExpression* is = static_cast<IsExpression*>(expression);

			visit(is->mExpression);
		} break;
		case Expression::ExpressionType::NewExpression: {
			visit(static_cast<NewExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::LiteralExpression: {
		} break;
		case Expression::ExpressionType::MethodExpression: {
			MethodExpression* method = static_cast<MethodExpression*>(expression);

			visit(method->mSymbolExpression);
			for ( ExpressionList::const_iterator it = method->mParams.begin(); it != method->mParams.end(); ++it ) {
				visit((*it));
			}
		} break;
		case Expression::ExpressionType::ScopeExpression: {
			ScopeExpression* scope = dynamic_cast<ScopeExpression*>(expression);

			visit(scope->mLHS);
			visit(scope->mRHS);
		} break;
		case Expression::ExpressionType::SymbolExpression: {
			SymbolExpression* sym = static_cast<SymbolExpression*>(expression);

			visit(sym->mSymbolExpression);
		} break;
		case Expression::ExpressionType::TernaryExpression: {
			TernaryExpression* ter = static_cast<TernaryExpression*>(expression);

			visit(ter->mCondition);
			visit(ter->mFirst);
			visit(ter->mSecond);
		} break;
		case Expression::ExpressionType::TypecastExpression: {
			TypecastExpression* type = static_cast<TypecastExpression*>(expression);

			visit(type->mExpression);
		} break;
		case Expression::ExpressionType::TypeidExpression: {
			visit(static_cast<TypeidExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::UnaryExpression: {
			UnaryExpression* un = static_cast<UnaryExpression*>(expression);

			visit(un->mExpression);
		} break;
	}
}

void TreeVisitor::visitFor(ForStatement* node)
{
	visitStatement(static_cast<Statement*>(node->mInitialization));

	visitStatement(static_cast<Statement*>(node->mIteration));

	visit(node->mStatement);
}

void TreeVisitor::visitForeach(ForeachStatement *node)
{
	visitStatement(node->mTypeDeclaration);

	visit(node->mStatement);
}

void TreeVisitor::visitIf(IfStatement* node)
{
	visit(node->mCondition);

	visit(node->mIfBlock);

	if ( node->mElseBlock ) {
		visit(node->mElseBlock);
	}
}

void TreeVisitor::visitOperator(Operator*)
{
}

void TreeVisitor::visitPrint(PrintStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitReturn(ReturnStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitStatement(Statement *node)
{
	if ( !node ) {
		return;
	}

	switch ( node->getStatementType() ) {
		case Statement::StatementType::AssertStatement:
			visitAssert(static_cast<AssertStatement*>(node));
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
		case Statement::StatementType::TypeInference:
			visitTypeInference(static_cast<TypeInference*>(node));
			break;
		case Statement::StatementType::WhileStatement:
			visitWhile(static_cast<WhileStatement*>(node));
			break;
	}
}

void TreeVisitor::visitStatements(Statements* node)
{
	Statements* statements = node;

	if ( statements ) {
		for ( Statements::Nodes::const_iterator it = statements->mNodes.begin(); it != statements->mNodes.end(); ++it ) {
			visit((*it));
		}
	}
}

void TreeVisitor::visitSwitch(SwitchStatement* node)
{
	visit(node->mExpression);

	for ( CaseStatements::const_iterator it = node->mCaseStatements.begin(); it != node->mCaseStatements.end(); ++it ) {
		visit((*it)->mCaseExpression);

		visit((*it)->mCaseBlock);
	}

	if ( node->mDefaultStatement ) {
		visit(node->mDefaultStatement);
	}
}

void TreeVisitor::visitThrow(ThrowStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitTry(TryStatement* node)
{
	visitStatement(node->mTryBlock);

	// TODO: handle catch statements

	for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
		if ( (*it)->mTypeDeclaration ) {
			//visitTypeDeclaration((*it)->mTypeDeclaration);

			visitStatements((*it)->mStatements);
		}
	}

	if ( node->mFinallyBlock ) {
		visitStatement(node->mFinallyBlock);
	}
}

void TreeVisitor::visitTypeDeclaration(TypeDeclaration* node)
{
	if ( node->mAssignment ) {
		visit(node->mAssignment);
	}
}

void TreeVisitor::visitTypeInference(TypeInference* node)
{
	if ( node->mAssignment ) {
		visit(node->mAssignment);
	}
}

void TreeVisitor::visitWhile(WhileStatement* node)
{
	visit(node->mCondition);

	visit(node->mStatement);
}


}
}
