
// Header
#include "PrintVisitor.h"

// Library includes
#include <iostream>
#include <Core/Common/Exceptions.h>

// Project includes

// Namespace declarations


namespace Slang {
namespace AST {


PrintVisitor::PrintVisitor()
: mIndentation(0)
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

	auto* expression = dynamic_cast<Expression*>(node);
	std::string result;

	switch ( expression->getExpressionType() ) {
		case Expression::ExpressionType::AssignmentExpression: {
			auto* assExp = dynamic_cast<AssignmentExpression*>(expression);

			result += printExpression(assExp->mLHS);
			result += " = ";
			result += printExpression(assExp->mRHS);
		} break;
		case Expression::ExpressionType::BinaryExpression: {
			auto* binExp = dynamic_cast<BinaryExpression*>(node);

			result += printExpression(binExp->mLHS) + " ";
			result += binExp->mOperation.content() + " ";
			result += printExpression(binExp->mRHS);
		} break;
		case Expression::ExpressionType::CopyExpression: {
			result += "copy " + printExpression(dynamic_cast<CopyExpression*>(expression)->mExpression);
		} break;
		case Expression::ExpressionType::IsExpression: {
			auto* isExp = dynamic_cast<IsExpression*>(expression);

			result += printExpression(isExp->mExpression) + " is " + isExp->mMatchType;
		} break;
		case Expression::ExpressionType::NewExpression: {
			auto* methodExp = dynamic_cast<MethodExpression*>(dynamic_cast<NewExpression*>(expression)->mExpression);

			result += "new " + dynamic_cast<NewExpression*>(expression)->getResultType();
			result += "(";
			for ( ExpressionList::const_iterator it = methodExp->mParams.begin(); it != methodExp->mParams.end(); ++it ) {
				if ( it != methodExp->mParams.begin() ) {
					result += ", ";
				}
				result += printExpression((*it));
			}
			result += ")";
		} break;
		case Expression::ExpressionType::LiteralExpression: {
			Runtime::AtomicValue value = dynamic_cast<LiteralExpression*>(expression)->mValue;
			if ( value.type() == Runtime::AtomicValue::Type::STRING ) {
				result += "\"";
			}
			result += value.toStdString();
			if ( value.type() == Runtime::AtomicValue::Type::STRING ) {
				result += "\"";
			}
		} break;
		case Expression::ExpressionType::MethodExpression: {
			auto* methodExp = dynamic_cast<MethodExpression*>(expression);

			result += printExpression(methodExp->mSymbolExpression);
			result += "(";
			for ( ExpressionList::const_iterator it = methodExp->mParams.begin(); it != methodExp->mParams.end(); ++it ) {
				if ( it != methodExp->mParams.begin() ) {
					result += ", ";
				}
				result += printExpression((*it));
			}
			result += ")";
		} break;
		case Expression::ExpressionType::ScopeExpression: {
			auto* scopeExp = dynamic_cast<ScopeExpression*>(expression);

			result += printExpression(scopeExp->mLHS);
			result += ".";
			result += printExpression(scopeExp->mRHS);
		} break;
		case Expression::ExpressionType::SymbolExpression: {
			auto* symExp = dynamic_cast<SymbolExpression*>(expression);

			result += symExp->mSymbolExpression ? printExpression(symExp->mSymbolExpression) : symExp->mName;
		} break;
		case Expression::ExpressionType::TernaryExpression: {
			auto* terExp = dynamic_cast<TernaryExpression*>(expression);

			result += printExpression(terExp->mCondition) + " ? ";
			result += printExpression(terExp->mFirst) + " : ";
			result += printExpression(terExp->mSecond);
		} break;
		case Expression::ExpressionType::TypecastExpression: {
			auto* tcExp = dynamic_cast<TypecastExpression*>(expression);

			result += "( " + tcExp->mDestinationType + " " + printExpression(tcExp->mExpression) + " )";
		} break;
		case Expression::ExpressionType::TypeidExpression: {
			result += "typeid( " + printExpression(dynamic_cast<TypeidExpression*>(expression)->mExpression) + " )";
		} break;
		case Expression::ExpressionType::UnaryExpression: {
			auto* unExp = dynamic_cast<UnaryExpression*>(expression);

			result += unExp->mOperation.content() + printExpression(unExp->mExpression);
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

void PrintVisitor::visitAssert(AssertStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "assert(" + printExpression(node->mExpression) + ");");
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

	visitStatement(dynamic_cast<Statement*>(node->mInitialization));

	mOutput.append("; " + printExpression(node->mCondition) + "; ");

	visitStatement(dynamic_cast<Statement*>(node->mIteration));

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

	mOutput.append(" : " + printExpression(node->mCollectionExpression) + " ) ");

	// reset indentation
	mIndentation = indent;

	visit(node->mStatement);
}

void PrintVisitor::visitIf(IfStatement* node)
{
	mOutput.insert(node->token().position(), printIndentation(mIndentation) + "if ( " + printExpression(node->mCondition) + " ) ");

	visit(node->mIfBlock);

	if ( node->mElseBlock ) {
		mOutput.insert(dynamic_cast<Statements*>(node->mElseBlock)->token().position(), printIndentation(mIndentation) + "else ");

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

	for ( auto it = node->mCaseStatements.cbegin(); it != node->mCaseStatements.cend(); ++it ) {
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

	// TODO: handle catch statements correctly

	for ( CatchStatements::const_iterator it = node->mCatchStatements.begin(); it != node->mCatchStatements.end(); ++it ) {
		mOutput.insert((*it)->mStatements->token().position(), printIndentation(mIndentation) + "catch ");

		if ( (*it)->mTypeDeclaration ) {
			mOutput.append("(");

			// set indentation to 0 temporarily
			int indent = mIndentation;
			mIndentation = 0;

			visitTypeDeclaration((*it)->mTypeDeclaration);

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
