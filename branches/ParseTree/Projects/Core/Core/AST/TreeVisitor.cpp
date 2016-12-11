
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

std::string PrintVisitor::printExpression(Expression* node) const
{
	std::string result;

	if ( node ) {
		switch ( node->getExpressionType() ) {
			case Expression::ExpressionType::BinaryExpression: {
				BinaryExpression* bin = static_cast<BinaryExpression*>(node);

				result += printExpression(bin->mLeft);
				result += " " + bin->mToken.content() + " ";
				result += printExpression(bin->mRight);
			} break;
			case Expression::ExpressionType::CopyExpression: {
				result += "copy " + printExpression(static_cast<CopyExpression*>(node)->mExpression);
			} break;
			case Expression::ExpressionType::NewExpression: {
				result += "new " + printExpression(static_cast<NewExpression*>(node)->mExpression);
			} break;
			case Expression::ExpressionType::LiteralExpression: {
				result += static_cast<LiteralExpression*>(node)->mValue.toStdString();
			} break;
			case Expression::ExpressionType::MethodExpression: {
				result += static_cast<MethodExpression*>(node)->mName;
			} break;
			case Expression::ExpressionType::VariableExpression: {
				result += static_cast<VariableExpression*>(node)->mName;
			} break;
		}
	}

	return result;
}

void PrintVisitor::process(Statements* root)
{
	Statements* statements = root ? root : mRootNode;

	if ( !statements ) {
		return;
	}

	for ( Statements::Nodes::const_iterator it = statements->mNodes.begin(); it != statements->mNodes.end(); ++it ) {
		switch ( (*it)->getNodeType() ) {
			case Node::NodeType::Expression:
				break;
			case Node::NodeType::Operator:
				break;
			case Node::NodeType::Statement:
				visitStatement((*it));
				break;
		}
	}
}

void PrintVisitor::visitAssert(AssertStatement* node)
{
	std::cout << "assert(" << printExpression(node->mExpression) << ");" << std::endl;
}

void PrintVisitor::visitAssignment(Assignment* node)
{
	std::cout << node->mName << " = " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitBreak(BreakStatement* /*node*/)
{
	std::cout << "break;" << std::endl;
}

void PrintVisitor::visitContinue(ContinueStatement* /*node*/)
{
	std::cout << "continue;" << std::endl;
}

void PrintVisitor::visitDelete(DeleteStatement* node)
{
	std::cout << "delete " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitExit(ExitStatement* node)
{
	std::cout << "exit(" << printExpression(node->mExpression) << ");" << std::endl;
}

void PrintVisitor::visitIf(IfStatement* node)
{
	std::cout << "if ( " << printExpression(node->mExpression) << " ) { " << std::endl;

	visitStatement(node->mIfBlock);

	std::cout << "}" << std::endl;

	if ( node->mElseBlock ) {
		std::cout << "else {" << std::endl;

		visitStatement(node->mElseBlock);

		std::cout << "}" << std::endl;
	}
}

void PrintVisitor::visitPrint(PrintStatement* node)
{
	std::cout << "print(" << printExpression(node->mExpression) << ");" << std::endl;
}

void PrintVisitor::visitReturn(ReturnStatement* node)
{
	std::cout << "return " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitThrow(ThrowStatement* node)
{
	std::cout << "throw " << printExpression(node->mExpression) << ";" << std::endl;
}

void PrintVisitor::visitWhile(WhileStatement* node)
{
	std::cout << "while ( " << printExpression(node->mExpression) << " ) {" << std::endl;

	visitStatement(node->mStatements);

	std::cout << "}" << std::endl;
}

void PrintVisitor::visitStatement(Statement* node)
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
		case Statement::StatementType::WhileStatement:
			visitWhile(static_cast<WhileStatement*>(node));
			break;
	}
}


}
}
