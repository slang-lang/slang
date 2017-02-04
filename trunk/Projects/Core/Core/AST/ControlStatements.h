
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
	explicit ExitStatement(Node* exp)
	: Statement(StatementType::ExitStatement),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class ReturnStatement : public Statement
{
public:
	explicit ReturnStatement(Node* exp)
	: Statement(StatementType::ReturnStatement),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class ThrowStatement : public Statement
{
public:
	explicit ThrowStatement(Node* exp)
	: Statement(StatementType::ThrowStatement),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


}
}


#endif
