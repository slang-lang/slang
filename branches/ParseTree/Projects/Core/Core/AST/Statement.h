
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
			ForeachStatement,
			ForStatement,
			IfStatement,
			PrintStatement,
			ReturnStatement,
			Statements,
			ThrowStatement,
			TryStatement,
			TypeDeclaration,
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
	Assignment(const Token& name, const Token& assignment, Node* exp)
	: Statement(StatementType::Assignment),
	  mAssignment(assignment),
	  mExpression(exp),
	  mName(name)
	{ }

public:
	Token mAssignment;
	Node* mExpression;
	Token mName;
};


class TypeDeclaration : public Statement
{
public:
	TypeDeclaration(const std::string& type, const std::string& name, Node* assignment)
	: Statement(StatementType::TypeDeclaration),
	  mAssignment(assignment),
	  mName(name),
	  mType(type)
	{ }

public:
	Node* mAssignment;
	std::string mName;
	std::string mType;
};


class Statements : public Statement
{
public:
	typedef std::list<Node*> Nodes;

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
