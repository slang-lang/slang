
// Header
#include "TreeVisitor.h"

// Library includes
#include <iostream>
#include <Core/Common/Exceptions.h>

// Project includes

// Namespace declarations


namespace Slang {
namespace AST {


void TreeVisitor::visit(Node* node)
{
	if ( node ) {
		switch ( node->getNodeType() ) {
			case Node::NodeType::Expression:
				visitExpression(dynamic_cast<Expression*>(node));
				break;
			case Node::NodeType::Operator:
				visitOperator(dynamic_cast<Operator*>(node));
				break;
			case Node::NodeType::Statement:
				visitStatement(dynamic_cast<Statement*>(node));
				break;
		}
	}
}

void TreeVisitor::visitAssert(AssertStatement* node)
{
	visit(node->mExpression);
}

void TreeVisitor::visitAssignment(AssignmentStatement* node)
{
	visitExpression( dynamic_cast<Expression*>( node->mLeftExpression ) );

	visitExpression( dynamic_cast<Expression*>( node->mRightExpression ) );
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
			auto* ass = dynamic_cast<AssignmentExpression*>(expression);

			visit(ass->mLHS);
			visit(ass->mRHS);
		} break;
		case Expression::ExpressionType::BinaryExpression: {
			auto* bin = dynamic_cast<BinaryExpression*>(expression);

			visit(bin->mLHS);
			visit(bin->mRHS);
		} break;
		case Expression::ExpressionType::CopyExpression: {
			visit(dynamic_cast<CopyExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::IsExpression: {
			auto* is = dynamic_cast<IsExpression*>(expression);

			visit(is->mExpression);
		} break;
		case Expression::ExpressionType::NewExpression: {
			visit(dynamic_cast<NewExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::LiteralExpression: {
		} break;
		case Expression::ExpressionType::MethodExpression: {
			auto* method = dynamic_cast<MethodExpression*>(expression);

			visit(method->mSymbolExpression);
			for ( ExpressionList::const_iterator it = method->mParams.begin(); it != method->mParams.end(); ++it ) {
				visit((*it));
			}
		} break;
		case Expression::ExpressionType::ScopeExpression: {
			auto* scope = dynamic_cast<ScopeExpression*>(expression);

			visit(scope->mLHS);
			visit(scope->mRHS);
		} break;
		case Expression::ExpressionType::SymbolExpression: {
			auto* sym = dynamic_cast<SymbolExpression*>(expression);

			visit(sym->mSymbolExpression);
		} break;
		case Expression::ExpressionType::TernaryExpression: {
			auto* ter = dynamic_cast<TernaryExpression*>(expression);

			visit(ter->mCondition);
			visit(ter->mFirst);
			visit(ter->mSecond);
		} break;
		case Expression::ExpressionType::TypecastExpression: {
			auto* type = dynamic_cast<TypecastExpression*>(expression);

			visit(type->mExpression);
		} break;
		case Expression::ExpressionType::TypeidExpression: {
			visit(dynamic_cast<TypeidExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::UnaryExpression: {
			auto* un = dynamic_cast<UnaryExpression*>(expression);

			visit(un->mExpression);
		} break;
	}
}

void TreeVisitor::visitFor(ForStatement* node)
{
	visitStatement(dynamic_cast<Statement*>(node->mInitialization));

	visitStatement(dynamic_cast<Statement*>(node->mIteration));

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
			visitAssert(dynamic_cast<AssertStatement*>(node));
			break;
		case Statement::StatementType::AssignmentStatement:
			visitAssignment(dynamic_cast<AssignmentStatement*>(node));
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

void TreeVisitor::visitStatements(Statements* node)
{
	Statements* statements = node;

	if ( statements ) {
		for ( auto& mNode : statements->mNodes ) {
			visit(mNode);
		}
	}
}

void TreeVisitor::visitSwitch(SwitchStatement* node)
{
	visit(node->mExpression);

	for ( auto& caseStatement : node->mCaseStatements ) {
		visit(caseStatement->mCaseExpression);

		visit(caseStatement->mCaseBlock);
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

	// TODO: handle catch statements correctly

	for ( auto& catchStatement : node->mCatchStatements ) {
		if ( catchStatement->mTypeDeclaration ) {
			//visitTypeDeclaration((*it)->mTypeDeclaration);

			visitStatements(catchStatement->mStatements);
		}
	}

	if ( node->mFinallyBlock ) {
		visitStatement(node->mFinallyBlock);
	}
}

void TreeVisitor::visitTypeDeclaration(TypeDeclaration* node)
{
	if ( node->mAssignmentExpression ) {
		visit(node->mAssignmentExpression);
	}
}

void TreeVisitor::visitTypeInference(TypeInference* node)
{
	visitTypeDeclaration( node );
}

void TreeVisitor::visitWhile(WhileStatement* node)
{
	visit(node->mCondition);

	visit(node->mStatement);
}


}
}
