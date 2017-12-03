
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
	explicit BreakStatement(const Token& token)
	: Statement(StatementType::BreakStatement, token)
	{ }
};


class ContinueStatement : public Statement
{
public:
	explicit ContinueStatement(const Token& token)
	: Statement(StatementType::ContinueStatement, token)
	{ }
};


class ExitStatement : public Statement
{
public:
	explicit ExitStatement(const Token& token, Node* exp)
	: Statement(StatementType::ExitStatement, token),
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
	explicit ReturnStatement(const Token& token, Node* exp)
	: Statement(StatementType::ReturnStatement, token),
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
	explicit ThrowStatement(const Token& token, Node* exp)
	: Statement(StatementType::ThrowStatement, token),
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
