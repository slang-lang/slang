
#ifndef ObjectiveScript_Core_AST_Keywords_h
#define ObjectiveScript_Core_AST_Keywords_h


#include "Statement.h"


namespace ObjectiveScript {
namespace AST {


class AssertStatement : public Statement
{
public:
	AssertStatement(Node* exp)
	: Statement(StatementType::AssertStatement),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class DeleteStatement : public Statement
{
public:
	DeleteStatement(Node* exp)
	: Statement(StatementType::DeleteStatement),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class ForeachStatement : public Statement
{
public:
	ForeachStatement(TypeDeclaration* typeDeclaration, const Token& loopVariable, Node* loopBlock)
	: Statement(StatementType::ForeachStatement),
	  mLoopBlock(loopBlock),
	  mLoopVariable(loopVariable),
	  mTypeDeclaration(typeDeclaration)
	{ }

public:
	Node* mLoopBlock;
	Token mLoopVariable;
	TypeDeclaration* mTypeDeclaration;
};


class ForStatement : public Statement
{
public:
	ForStatement(Node* initialization, Node* condition, Node* iteration, Node* loopBlock)
	: Statement(StatementType::ForStatement),
	  mCondition(condition),
	  mInitialization(initialization),
	  mIteration(iteration),
	  mLoopBlock(loopBlock)
	{ }

public:
	Node* mCondition;
	Node* mInitialization;
	Node* mIteration;
	Node* mLoopBlock;
};


class IfStatement : public Statement
{
public:
	IfStatement(Node* exp, Node* ifBlock, Node* elseBlock)
	: Statement(StatementType::IfStatement),
	  mElseBlock(elseBlock),
	  mExpression(exp),
	  mIfBlock(ifBlock)
	{ }

public:
	Node* mElseBlock;
	Node* mExpression;
	Node* mIfBlock;
};


class PrintStatement : public Statement
{
public:
	PrintStatement(Node* exp)
	: Statement(StatementType::PrintStatement),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class TryStatement : public Statement
{
public:
	TryStatement(Statements* tryBlock, Statements* finallyBlock)
	: Statement(StatementType::TryStatement),
	  mFinallyBlock(finallyBlock),
	  mTryBlock(tryBlock)
	{ }

public:
	//CatchBlocks* mCatchBlocks;
	Statements* mFinallyBlock;
	Statements* mTryBlock;
};


class WhileStatement : public Statement
{
public:
	WhileStatement(Node* condition, Node* statements)
	: Statement(StatementType::WhileStatement),
	  mExpression(condition),
	  mStatements(statements)
	{ }

public:
	Node* mExpression;
	Node* mStatements;
};


}
}


#endif