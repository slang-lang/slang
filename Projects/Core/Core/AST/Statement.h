
#ifndef ObjectiveScript_Core_AST_Statement_h
#define ObjectiveScript_Core_AST_Statement_h


// Library includes
#include <list>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Symbol.h>
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
			CaseStatement,
			CatchStatement,
			ContinueStatement,
			DeleteStatement,
			ExitStatement,
			ForeachStatement,
			ForStatement,
			IfStatement,
			PrintStatement,
			ReturnStatement,
			Statements,
			SwitchStatement,
			ThrowStatement,
			TryStatement,
			TypeDeclaration,
			WhileStatement
		};
	};

public:
	explicit Statement(StatementType::E statementType)
	: Node(NodeType::Statement),
	  mStatementType(statementType)
	{ }
	virtual ~Statement() { }

	StatementType::E getStatementType() const {
		return mStatementType;
	}

protected:
	StatementType::E mStatementType;
};


class Assignment : public Statement
{
public:
	Assignment(SymbolExpression* lvalue, const Token& assignment, Node* rvalue, const std::string& /*resultType*/)
	: Statement(StatementType::Assignment),
	  mAssignment(assignment),
	  mExpression(rvalue),
	  mLValue(lvalue)
	{ }
	~Assignment() {
		delete mExpression;
		//delete mLValue;
		mLValue = 0;
	}

public:
	Token mAssignment;
	Node* mExpression;
	SymbolExpression* mLValue;
};


class TypeDeclaration : public Statement
{
public:
	TypeDeclaration(Symbol* symbol, const PrototypeConstraints& constraints, const std::string& name, bool isConst, bool isReference, Node* assignment)
	: Statement(StatementType::TypeDeclaration),
	  mAssignment(assignment),
	  mConstraints(constraints),
	  mIsConst(isConst),
	  mIsReference(isReference),
	  mName(name),
	  mSymbol(symbol)
	{ }
	~TypeDeclaration() {
		delete mAssignment;
		mSymbol = 0;
	}

public:
	Node* mAssignment;
	PrototypeConstraints mConstraints;
	bool mIsConst;
	bool mIsReference;
	std::string mName;
	Symbol* mSymbol;
};


class Statements : public Statement
{
public:
	typedef std::list<Node*> Nodes;

public:
	Statements()
	: Statement(StatementType::Statements)
	{ }
	~Statements() {
		for ( Nodes::iterator it = mNodes.begin(); it != mNodes.end(); ++it ) {
			delete (*it);
		}
	}

public:
	Nodes mNodes;
};


}
}

#endif
