
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
			AssertStatement = 0,
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
			TypeInference,
			WhileStatement
		};
	};

public:
	explicit Statement(StatementType::E statementType, const Token& token)
	: Node(NodeType::Statement),
	  mStatementType(statementType),
	  mToken(token)
	{ }
	virtual ~Statement() { }

	StatementType::E getStatementType() const {
		return mStatementType;
	}

	const Token& token() const {
		return mToken;
	}

protected:
	StatementType::E mStatementType;
	Token mToken;
};


class Assignment : public Statement
{
public:
	Assignment(SymbolExpression* lvalue, const Token& assignment, Node* rvalue, const std::string& /*resultType*/)
	: Statement(StatementType::Assignment, assignment),
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
	TypeDeclaration(const Token& token, const std::string& type, const PrototypeConstraints& constraints, const std::string& name, bool isConst, bool isReference, Node* assignment)
	: Statement(StatementType::TypeDeclaration, token),
	  mAssignment(assignment),
	  mConstraints(constraints),
	  mIsConst(isConst),
	  mIsReference(isReference),
	  mName(name),
	  mType(type)
	{ }
	~TypeDeclaration() {
		delete mAssignment;
	}

public:
	Node* mAssignment;
	PrototypeConstraints mConstraints;
	bool mIsConst;
	bool mIsReference;
	std::string mName;
	std::string mType;
};


class TypeInference : public TypeDeclaration
{
public:
	TypeInference(const Token& token, const std::string& type, const PrototypeConstraints& constraints, const std::string& name, bool isConst, bool isReference, Node* assignment)
	: TypeDeclaration(token, type, constraints, name, isConst, isReference, assignment)
	{
		mStatementType = Statement::StatementType::TypeInference;
	}
};


class Statements : public Statement
{
public:
	typedef std::list<Node*> Nodes;

public:
	explicit Statements(const Token& token)
	: Statement(StatementType::Statements, token)
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
