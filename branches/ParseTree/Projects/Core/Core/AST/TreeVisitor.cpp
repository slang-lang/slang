
#include "TreeVisitor.h"


// Library includes
#include <iostream>

// Project includes
//#include "ControlStatements.h"
//#include "Expression.h"
//#include "Keywords.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeVisitor::TreeVisitor(Statements *root)
: mRootNode(root)
{
}

TreeVisitor::~TreeVisitor()
{
}



PrintVisitor::PrintVisitor(Statements *root)
: TreeVisitor(root),
  mIndentation(0)
{
}

PrintVisitor::~PrintVisitor()
{
}

std::string PrintVisitor::printExpression(Node* node) const
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

std::string PrintVisitor::printIndentation(int indentation) const
{
	std::string result;

	for ( int i = 0; i < indentation; i++ ) {
		result += "\t";
	}

	return result;
}

void PrintVisitor::process(Statements* root)
{
	std::cout << printIndentation(mIndentation) << "{" << std::endl;
	mIndentation++;

	Statements* statements = root ? root : mRootNode;

	if ( statements ) {
		for ( Statements::Nodes::const_iterator it = statements->mNodes.begin(); it != statements->mNodes.end(); ++it ) {
			visit((*it));
		}
	}

	mIndentation--;
	std::cout << printIndentation(mIndentation) << "}" << std::endl;
}

void PrintVisitor::visit(Node* node)
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

void PrintVisitor::visitAssert(AssertStatement* node)
{
	std::cout << printIndentation(mIndentation) << "assert(" << printExpression(node->mExpression) << ");" << std::endl;
}

void PrintVisitor::visitAssignment(Assignment* node)
{
	std::cout << printIndentation(mIndentation) << node->mName.content() << " " << node->mAssignment.content() << " " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitBreak(BreakStatement* /*node*/)
{
	std::cout << printIndentation(mIndentation) << "break;" << std::endl;
}

void PrintVisitor::visitContinue(ContinueStatement* /*node*/)
{
	std::cout << printIndentation(mIndentation) << "continue;" << std::endl;
}

void PrintVisitor::visitDelete(DeleteStatement* node)
{
	std::cout << printIndentation(mIndentation) << "delete " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitExit(ExitStatement* node)
{
	std::cout << printIndentation(mIndentation) << "exit " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitExpression(Expression *expression)
{
	std::cout << printIndentation(mIndentation) << printExpression(expression) << ";" << std::endl;
}

void PrintVisitor::visitFor(ForStatement* node)
{
	std::cout << printIndentation(mIndentation) << "for ( ";

	visitStatement(static_cast<Statement*>(node->mInitialization));

	mIndentation++;

	std::cout << printIndentation(mIndentation) << printExpression(node->mCondition) << "; " << std::endl;

	visitStatement(static_cast<Statement*>(node->mIteration));

	mIndentation--;

	std::cout << printIndentation(mIndentation) << ") ";

	visit(node->mLoopBlock);
}

void PrintVisitor::visitForeach(ForeachStatement *node)
{
	std::cout << printIndentation(mIndentation) << "for ( ";

	visitStatement(node->mTypeDeclaration);

	std::cout << " : " << node->mLoopVariable.content() << " ) ";

	visit(node->mLoopBlock);
}

void PrintVisitor::visitIf(IfStatement* node)
{
	std::cout << printIndentation(mIndentation) << "if ( " << printExpression(node->mExpression) << " ) ";

	visit(node->mIfBlock);

	if ( node->mElseBlock && static_cast<Statements*>(node->mElseBlock)->mNodes.size() > 0 ) {
		std::cout << printIndentation(mIndentation) << "else ";

		visit(node->mElseBlock);
	}
}

void PrintVisitor::visitOperator(Operator* /*op*/)
{
	std::cout << "Operator" << std::endl;
}

void PrintVisitor::visitPrint(PrintStatement* node)
{
	std::cout << printIndentation(mIndentation) << "print(" << printExpression(node->mExpression) << ");" << std::endl;
}

void PrintVisitor::visitReturn(ReturnStatement* node)
{
	std::cout << printIndentation(mIndentation) << "return " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitStatement(Statement *node)
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

void PrintVisitor::visitThrow(ThrowStatement* node)
{
	std::cout << printIndentation(mIndentation) << "throw " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitTry(TryStatement* node)
{
	std::cout << printIndentation(mIndentation) << "try ";

	visitStatement(node->mTryBlock);

	if ( node->mFinallyBlock ) {
		std::cout << printIndentation(mIndentation) << "finally ";

		visitStatement(node->mFinallyBlock);
	}
}

void PrintVisitor::visitTypeDeclaration(TypeDeclaration* node)
{
	std::cout << printIndentation(mIndentation) << node->mType << " " << node->mName;

	if ( node->mAssignment ) {
		std::cout << " = " << printExpression(node->mAssignment) << ";" << std::endl;
	}
}

void PrintVisitor::visitWhile(WhileStatement* node)
{
	std::cout << printIndentation(mIndentation) << "while ( " << printExpression(node->mExpression) << " ) ";

	visit(node->mStatements);
}


}
}
