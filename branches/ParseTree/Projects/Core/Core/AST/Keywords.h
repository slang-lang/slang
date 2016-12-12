
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
	ForeachStatement(TypeDeclaration* typeDeclaration, Statements* loopBlock)
	: Statement(StatementType::ForeachStatement),
	  mLoopBlock(loopBlock),
	  mTypeDeclaration(typeDeclaration)
	{ }

public:
	Statements* mLoopBlock;
	TypeDeclaration* mTypeDeclaration;
};


class ForStatement : public Statement
{
public:
	ForStatement(Statement* initialization, Node* condition, Statement* iteration, Statements* loopBlock)
	: Statement(StatementType::ForStatement),
	  mCondition(condition),
	  mInitialization(initialization),
	  mIteration(iteration),
	  mLoopBlock(loopBlock)
	{ }

public:
	Node* mCondition;
	Statement* mInitialization;
	Statement* mIteration;
	Statements* mLoopBlock;
};


class IfStatement : public Statement
{
public:
	IfStatement(Node* exp, Statements* ifBlock, Statements* elseBlock)
	: Statement(StatementType::IfStatement),
	  mElseBlock(elseBlock),
	  mExpression(exp),
	  mIfBlock(ifBlock)
	{ }

public:
	Statements* mElseBlock;
	Node* mExpression;
	Statements* mIfBlock;
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
	WhileStatement(Node* condition, Statement* statements)
	: Statement(StatementType::WhileStatement),
	  mExpression(condition),
	  mStatements(statements)
	{ }

public:
	Node* mExpression;
	Statement* mStatements;
};


}
}


#endif