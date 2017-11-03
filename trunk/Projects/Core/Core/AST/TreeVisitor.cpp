
// Header
#include "TreeVisitor.h"

// Library includes
#include <iostream>
#include <Core/Common/Exceptions.h>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


PrintVisitor::PrintVisitor()
: mIndentation(0)
{
}

PrintVisitor::~PrintVisitor()
{
}

void PrintVisitor::generate(Statements* root, TreeLineBuffer& output)
{
	// clean up old output
	mOutput.clear();

	// start processing beginning with our given root node
	visitStatements(root);

	// provide our callee with our collected output
	output.insert(mOutput);
}

std::string PrintVisitor::printExpression(Node* node) const
{
	if ( !node ) {
		return "";
	}

	assert(node->getNodeType() == Node::NodeType::Expression);

	Expression* expression = static_cast<Expression*>(node);
	std::string result;

	switch ( expression->getExpressionType() ) {
		case Expression::ExpressionType::BinaryExpression: {
			BinaryExpression* bin = static_cast<BinaryExpression*>(node);

			result += printExpression(bin->mLeft) + " ";
			result += bin->mOperation.content() + " ";
			result += printExpression(bin->mRight);
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
			Runtime::AtomicValue value = static_cast<LiteralExpression*>(expression)->mValue;
			if ( value.type() == Runtime::AtomicValue::Type::STRING ) {
				result += "\"";
			}
			result += value.toStdString();
			if ( value.type() == Runtime::AtomicValue::Type::STRING ) {
				result += "\"";
			}
		} break;
		case Expression::ExpressionType::MethodExpression: {
			result += printExpression(static_cast<MethodExpression*>(expression)->mSymbolExpression);
			result += "(";
			for ( ExpressionList::const_iterator it = static_cast<MethodExpression*>(expression)->mParams.begin();
				  it != static_cast<MethodExpression*>(expression)->mParams.end();
				  ++it ) {
				result += printExpression((*it));
			}
			result += ")";
		} break;
		case Expression::ExpressionType::SymbolExpression: {
			result += static_cast<SymbolExpression*>(expression)->mSymbolExpression
					  ? printExpression(static_cast<SymbolExpression*>(expression)->mSymbolExpression)
					  : static_cast<SymbolExpression*>(expression)->mName;
		} break;
		case Expression::ExpressionType::TernaryExpression: {
			result += printExpression(static_cast<TernaryExpression*>(expression)->mCondition) + " ? ";
			result += printExpression(static_cast<TernaryExpression*>(expression)->mFirst) + " : ";
			result += printExpression(static_cast<TernaryExpression*>(expression)->mSecond);
		} break;
		case Expression::ExpressionType::TypecastExpression: {
			result += "( " + static_cast<TypecastExpression*>(expression)->mDestinationType + " ";
			result += printExpression(static_cast<TypecastExpression*>(expression)->mExpression) + " )";
		} break;
		case Expression::ExpressionType::TypeidExpression: {
			result += "typeid( " + printExpression(static_cast<TypeidExpression*>(expression)->mExpression) + " )";
		} break;
		case Expression::ExpressionType::UnaryExpression: {
			result += static_cast<UnaryExpression*>(expression)->mOperation.content();
			result += printExpression(static_cast<UnaryExpression*>(expression)->mExpression);
		} break;
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
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "assert(" + printExpression(node->mExpression) + ");");
}

void PrintVisitor::visitAssignment(Assignment* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + node->mLValue->mName + " " + node->mAssignment.content() + " " + printExpression(node->mExpression));
}

void PrintVisitor::visitBreak(BreakStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "break;");
}

void PrintVisitor::visitContinue(ContinueStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "continue;");
}

void PrintVisitor::visitDelete(DeleteStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "delete " + printExpression(node->mExpression) + ";");
}

void PrintVisitor::visitExit(ExitStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "exit( " + printExpression(node->mExpression) + " );");
}

void PrintVisitor::visitExpression(Expression* expression)
{
	mOutput.append(printIndentation(mIndentation) + printExpression(expression));
}

void PrintVisitor::visitFor(ForStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "for ( ");

	// set indentation to 0 temporarily
	int indent = mIndentation;
	mIndentation = 0;

	visitStatement(static_cast<Statement*>(node->mInitialization));

	mOutput.append("; " + printExpression(node->mCondition) + "; ");

	visitStatement(static_cast<Statement*>(node->mIteration));

	mOutput.append(" ) ");

	// reset indentation
	mIndentation = indent;

	visit(node->mStatement);
}

void PrintVisitor::visitForeach(ForeachStatement *node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "for ( ");

	// set indentation to 0 temporarily
	int indent = mIndentation;
	mIndentation = 0;

	visitStatement(node->mTypeDeclaration);

	mOutput.append(" : " + printExpression(node->mLoopExpression) + " ) ");

	// reset indentation
	mIndentation = indent;

	visit(node->mStatement);
}

void PrintVisitor::visitIf(IfStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "if ( " + printExpression(node->mCondition) + " ) ");

	visit(node->mIfBlock);

	if ( node->mElseBlock ) {
		mOutput.insert(static_cast<Statements*>(node->mElseBlock)->token().position(), printIndentation(mIndentation) + "else ");

		visit(node->mElseBlock);
	}
}

void PrintVisitor::visitOperator(Operator* op)
{
	mOutput.append(op->token().content());
}

void PrintVisitor::visitPrint(PrintStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "print(" + printExpression(node->mExpression) + ");");
}

void PrintVisitor::visitReturn(ReturnStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "return " + printExpression(node->mExpression) + ";");
}

void PrintVisitor::visitStatement(Statement *node)
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

void PrintVisitor::visitStatements(Statements* node)
{
	mOutput.append("{ ");
	mIndentation++;

	Statements* statements = node;

	if ( statements ) {
		for ( Statements::Nodes::const_iterator it = statements->mNodes.begin(); it != statements->mNodes.end(); ++it ) {
			visit((*it));
		}
	}

	mIndentation--;
	mOutput.append(" }");
}

void PrintVisitor::visitSwitch(SwitchStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "switch ( " + printExpression(node->mExpression) + " ) {");

	for ( CaseStatements::const_iterator it = node->mCaseStatements.begin(); it != node->mCaseStatements.end(); ++it ) {
		mOutput.insert(node->token().position(), printIndentation(mIndentation + 1) + printExpression((*it)->mCaseExpression) + ": ");

		visit((*it)->mCaseBlock);
	}

	if ( node->mDefaultStatement ) {
		mOutput.insert(node->token().position(), printIndentation(mIndentation + 1) + "default: ");

		visit(node->mDefaultStatement);
	}

	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "}");
}

void PrintVisitor::visitThrow(ThrowStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "throw " + printExpression(node->mExpression) + ";");
}

void PrintVisitor::visitTry(TryStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "try ");

	visitStatement(node->mTryBlock);

	// TODO: handle catch statements

	for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
		mOutput.insert((*it)->mStatements->token().position(), printIndentation(mIndentation) + "catch ");

		if ( (*it)->mTypeDeclaration ) {
			mOutput.append("(");

			// set indentation to 0 temporarily
			int indent = mIndentation;
			mIndentation = 0;

			//visitTypeDeclaration((*it)->mTypeDeclaration);

			// reset indentation
			mIndentation = indent;

			mOutput.append(") ");

			visitStatements((*it)->mStatements);
		}
	}

	if ( node->mFinallyBlock ) {
		mOutput.insert(node->mFinallyBlock->token().position(), printIndentation(mIndentation) + "finally ");

		visitStatement(node->mFinallyBlock);
	}
}

void PrintVisitor::visitTypeDeclaration(TypeDeclaration* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + node->mType + " " + node->mName);

	if ( node->mAssignment ) {
		mOutput.insert(node->token().position(), " = " + printExpression(node->mAssignment));
	}
}

void PrintVisitor::visitTypeInference(TypeInference* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "var " + node->mName);

	if ( node->mAssignment ) {
		mOutput.insert(node->token().position(), " = " + printExpression(node->mAssignment));
	}
}

void PrintVisitor::visitWhile(WhileStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "while ( " + printExpression(node->mCondition) + " ) ");

	visit(node->mStatement);
}


}
}
