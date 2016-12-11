
#ifndef ObjectiveScript_Core_AST_ControlStatements_h
#define ObjectiveScript_Core_AST_ControlStatements_h


#include "Statement.h"


namespace ObjectiveScript {
namespace AST {


class BreakStatement : public Statement
{
public:
	BreakStatement()
	: Statement(StatementType::BreakStatement)
	{ }
};


class ContinueStatement : public Statement
{
public:
	ContinueStatement()
	: Statement(StatementType::ContinueStatement)
	{ }
};


class ExitStatement : public Statement
{
public:
	ExitStatement(Expression* exp)
	: Statement(StatementType::ExitStatement),
	  mExpression(exp)
	{ }

public:
	Expression* mExpression;
};


class ReturnStatement : public Statement
{
public:
	ReturnStatement(Expression* exp)
	: Statement(StatementType::ReturnStatement),
	  mExpression(exp)
	{ }

public:
	Expression* mExpression;
};


class ThrowStatement : public Statement
{
public:
	ThrowStatement(Expression* exp)
	: Statement(StatementType::ThrowStatement),
	  mExpression(exp)
	{ }

public:
	Expression* mExpression;
};


}
}


#endif
