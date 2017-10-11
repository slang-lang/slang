
// Header
#include "TreeVisitor.h"

// Library includes
#include <iostream>
#include <Core/Common/Exceptions.h>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


ATreeVisitor::~ATreeVisitor()
{
}

void ATreeVisitor::visit(Node* node)
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

void ATreeVisitor::visitAssert(AssertStatement* node)
{
	assert(node);

	visit(node->mExpression);
}

void ATreeVisitor::visitAssignment(Assignment* node)
{
	assert(node);

	visit(node->mLValue);

	visit(node->mExpression);
}

void ATreeVisitor::visitBreak(BreakStatement* node)
{
	(void)node;
}

void ATreeVisitor::visitContinue(ContinueStatement* node)
{
	(void)node;
}

void ATreeVisitor::visitDelete(DeleteStatement* node)
{
	assert(node);

	visit(node->mExpression);
}

void ATreeVisitor::visitExit(ExitStatement* node)
{
	assert(node);

	visit(node->mExpression);
}

void ATreeVisitor::visitExpression(Expression* expression)
{
	if ( !expression ) {
		return;
	}

	switch ( expression->getExpressionType() ) {
		case Expression::ExpressionType::BinaryExpression: {
			visit(static_cast<Expression*>(static_cast<BinaryExpression*>(expression)->mLeft));
			visit(static_cast<Expression*>(static_cast<BinaryExpression*>(expression)->mRight));
		} break;
		case Expression::ExpressionType::CopyExpression: {
			visit(static_cast<Expression*>(static_cast<CopyExpression*>(expression)->mExpression));
		} break;
		case Expression::ExpressionType::IsExpression: {
			visit(static_cast<Expression*>(static_cast<IsExpression*>(expression)->mExpression));
		} break;
		case Expression::ExpressionType::NewExpression: {
			visit(static_cast<Expression*>(static_cast<NewExpression*>(expression)->mExpression));
		} break;
		case Expression::ExpressionType::LiteralExpression: {
		} break;
		case Expression::ExpressionType::MethodExpression: {
			visit(static_cast<Expression*>(static_cast<MethodExpression*>(expression)->mSymbolExpression));

			for ( ExpressionList::const_iterator it = static_cast<MethodExpression*>(expression)->mParams.begin();
				  it != static_cast<MethodExpression*>(expression)->mParams.end();
				  ++it ) {
				visit(static_cast<Expression*>((*it)));
			}
		} break;
		case Expression::ExpressionType::SymbolExpression: {
			visit(static_cast<Expression*>(static_cast<SymbolExpression*>(expression)->mSymbolExpression));
		} break;
		case Expression::ExpressionType::TernaryExpression: {
			visit(static_cast<Expression*>(static_cast<TernaryExpression*>(expression)->mCondition));
			visit(static_cast<Expression*>(static_cast<TernaryExpression*>(expression)->mFirst));
			visit(static_cast<Expression*>(static_cast<TernaryExpression*>(expression)->mSecond));
		} break;
		case Expression::ExpressionType::TypecastExpression: {
			visit(static_cast<Expression*>(static_cast<TypecastExpression*>(expression)->mExpression));
		} break;
		case Expression::ExpressionType::TypeidExpression: {
			visit(static_cast<Expression*>(static_cast<TypeidExpression*>(expression)->mExpression));
		} break;
		case Expression::ExpressionType::UnaryExpression: {
			visit(static_cast<Expression*>(static_cast<UnaryExpression*>(expression)->mExpression));
		} break;
	}
}

void ATreeVisitor::visitFor(ForStatement* node)
{
	assert(node);

	visit(node->mCondition);

	visit(node->mInitialization);

	visit(node->mIteration);

	visit(node->mStatement);
}

void ATreeVisitor::visitForeach(ForeachStatement *node)
{
	assert(node);

	visit(node->mLoopVariable);

	visit(node->mTypeDeclaration);

	visit(node->mStatement);
}

void ATreeVisitor::visitIf(IfStatement* node)
{
	assert(node);

	visit(node->mCondition);

	visit(node->mIfBlock);

	if ( node->mElseBlock ) {
		visit(node->mElseBlock);
	}
}

void ATreeVisitor::visitOperator(Operator* op)
{
	(void)op;
}

void ATreeVisitor::visitPrint(PrintStatement* node)
{
	assert(node);

	visit(node->mExpression);
}

void ATreeVisitor::visitReturn(ReturnStatement* node)
{
	assert(node);

	visit(node->mExpression);
}

void ATreeVisitor::visitStatement(Statement *node)
{
	if ( !node ) {
		return;
	}

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
		case Statement::StatementType::TypeInference:
			visitTypeInference(static_cast<TypeInference*>(node));
			break;
		case Statement::StatementType::WhileStatement:
			visitWhile(static_cast<WhileStatement*>(node));
			break;
	}
}

void ATreeVisitor::visitStatements(Statements* node)
{
	if ( !node ) {
		return;
	}

	for ( Statements::Nodes::const_iterator it = node->mNodes.begin(); it != node->mNodes.end(); ++it ) {
		visit((*it));
	}
}

void ATreeVisitor::visitSwitch(SwitchStatement* node)
{
	assert(node);

	for ( CaseStatements::const_iterator it = node->mCaseStatements.begin(); it != node->mCaseStatements.end(); ++it ) {
		visit((*it)->mCaseBlock);
	}

	if ( node->mDefaultStatement ) {
		visit(node->mDefaultStatement);
	}
}

void ATreeVisitor::visitThrow(ThrowStatement* node)
{
	assert(node);

	visit(node->mExpression);
}

void ATreeVisitor::visitTry(TryStatement* node)
{
	assert(node);

	visit(node->mTryBlock);

	for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
		if ( (*it)->mTypeDeclaration ) {
			visitStatements((*it)->mStatements);
		}
	}

	if ( node->mFinallyBlock ) {
		visit(node->mFinallyBlock);
	}
}

void ATreeVisitor::visitTypeDeclaration(TypeDeclaration* node)
{
	assert(node);

	visit(node->mAssignment);
}

void ATreeVisitor::visitTypeInference(TypeInference* node)
{
	assert(node);

	visit(node->mAssignment);
}

void ATreeVisitor::visitWhile(WhileStatement* node)
{
	assert(node);

	visit(node->mCondition);

	visit(node->mStatement);
}


}
}
