
#ifndef ObjectiveScript_Core_AST_Keywords_h
#define ObjectiveScript_Core_AST_Keywords_h


#include "Statement.h"


namespace ObjectiveScript {
namespace AST {


class AssertStatement : public Statement
{
public:
	AssertStatement(Expression* exp)
	: Statement(StatementType::AssertStatement),
	  mExpression(exp)
	{ }

public:
	Expression* mExpression;
};


class DeleteStatement : public Statement
{
public:
	DeleteStatement(VariableExpression* exp)
	: Statement(StatementType::DeleteStatement),
	  mExpression(exp)
	{ }

public:
	VariableExpression* mExpression;
};


class IfStatement : public Statement
{
public:
	IfStatement(Expression* exp, Statements* ifBlock, Statements* elseBlock)
	: Statement(StatementType::IfStatement),
	  mElseBlock(elseBlock),
	  mExpression(exp),
	  mIfBlock(ifBlock)
	{ }

public:
	Statements* mElseBlock;
	Expression* mExpression;
	Statements* mIfBlock;
};


class PrintStatement : public Statement
{
public:
	PrintStatement(Expression* exp)
	: Statement(StatementType::PrintStatement),
	  mExpression(exp)
	{ }

public:
	Expression* mExpression;
};


class WhileStatement : public Statement
{
public:
	WhileStatement(Expression* condition, Statement* statements)
	: Statement(StatementType::WhileStatement),
	  mExpression(condition),
	  mStatements(statements)
	{ }

public:
	Expression* mExpression;
	Statement* mStatements;
};


}
}


#endif