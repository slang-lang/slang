
#ifndef ObjectiveScript_Core_AST_Statement_h
#define ObjectiveScript_Core_AST_Statement_h


// Library includes
#include <list>

// Project includes
#include <Core/Reference.h>
#include "Expression.h"
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class Statement : public Node
{
public:
	class StatementType {
	public:
		enum E {
			AssertStatement,
			Assignment,
			BreakStatement,
			ContinueStatement,
			DeleteStatement,
			ExitStatement,
			IfStatement,
			PrintStatement,
			ReturnStatement,
			Statements,
			ThrowStatement,
			WhileStatement
		};
	};

public:
	Statement(StatementType::E statementType)
	: Node(NodeType::Statement),
	  mStatementType(statementType)
	{ }

	StatementType::E getStatementType() const {
		return mStatementType;
	}

protected:
	StatementType::E mStatementType;
};


class Assignment : public Statement
{
public:
	Assignment(const std::string& name, Expression* exp)
	: Statement(StatementType::Assignment),
	  mExpression(exp),
	  mName(name)
	{ }

public:
	Expression* mExpression;
	std::string mName;
};


class Statements : public Statement
{
public:
	typedef std::list<Statement*> Nodes;

public:
	Statements()
	: Statement(StatementType::Statements)
	{ }

public:
	Nodes mNodes;
};


}
}

#endif
