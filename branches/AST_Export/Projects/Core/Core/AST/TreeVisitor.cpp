
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

void ATreeVisitor::visitAssert(AssertStatement* node)
{
	(void)node;
}

void ATreeVisitor::visitAssignment(Assignment* node)
{
	(void)node;
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
	(void)node;
}

void ATreeVisitor::visitExit(ExitStatement* node)
{
	(void)node;
}

void ATreeVisitor::visitExpression(Expression* expression)
{
	(void)expression;
}

void ATreeVisitor::visitFor(ForStatement* node)
{
	assert(node);

	visitStatement(static_cast<Statement*>(node->mInitialization));

	visitStatement(static_cast<Statement*>(node->mIteration));

	visit(node->mStatement);
}

void ATreeVisitor::visitForeach(ForeachStatement *node)
{
	assert(node);

	visitStatement(node->mTypeDeclaration);

	visit(node->mStatement);
}

void ATreeVisitor::visitIf(IfStatement* node)
{
	assert(node);

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
	(void)node;
}

void ATreeVisitor::visitReturn(ReturnStatement* node)
{
	(void)node;
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
	(void)node;
}

void ATreeVisitor::visitTry(TryStatement* node)
{
	assert(node);

	visitStatement(node->mTryBlock);

	for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
		if ( (*it)->mTypeDeclaration ) {
			visitStatements((*it)->mStatements);
		}
	}

	if ( node->mFinallyBlock ) {
		visitStatement(node->mFinallyBlock);
	}
}

void ATreeVisitor::visitTypeDeclaration(TypeDeclaration* node)
{
	(void)node;
}

void ATreeVisitor::visitTypeInference(TypeInference* node)
{
	(void)node;
}

void ATreeVisitor::visitWhile(WhileStatement* node)
{
	assert(node);

	visitExpression(static_cast<Expression*>(node->mCondition));

	visit(node->mStatement);
}


}
}
