
#ifndef ObjectiveScript_Core_AST_ControlStatements_h
#define ObjectiveScript_Core_AST_ControlStatements_h


// Library includes

// Project includes
#include "Statement.h"

// Forward declarations

// Namespace declarations


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
	~ExitStatement() {
		delete mExpression;
	}

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
	~ReturnStatement() {
		delete mExpression;
	}

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
	~ThrowStatement() {
		delete mExpression;
	}

public:
	Node* mExpression;
};


}
}


#endif
