
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



class AssertStatement : public Statement
{
public:
	AssertStatement(const Token& token, Node* exp)
	: Statement(StatementType::AssertStatement, token),
	  mExpression(exp),
	  mPosition(token.position())
	{ }
	~AssertStatement() {
		delete mExpression;
	}

public:
	Node* mExpression;
	Common::Position mPosition;
};


class BreakStatement : public Statement
{
public:
	explicit BreakStatement(const Token& token)
	: Statement(StatementType::BreakStatement, token)
	{ }
};


class CaseStatement : public Statement
{
public:
	CaseStatement(const Token& token, Node* caseExpression, Statements* caseBlock)
	: Statement(StatementType::CaseStatement, token),
	  mCaseBlock(caseBlock),
	  mCaseExpression(caseExpression)
	{ }
	~CaseStatement() {
		delete mCaseBlock;
		delete mCaseExpression;
	}

public:
	Statements* mCaseBlock;
	Node* mCaseExpression;
};

typedef std::list<CaseStatement*> CaseStatements;

class CatchStatement : public Statement
{
public:
	CatchStatement(const Token& token, TypeDeclaration* typeDeclaration, Statements* statements)
	: Statement(StatementType::CatchStatement, token),
	  mStatements(statements),
	  mTypeDeclaration(typeDeclaration)
	{ }
	~CatchStatement() {
		delete mStatements;
		delete mTypeDeclaration;
	}

public:
	Statements* mStatements;
	TypeDeclaration* mTypeDeclaration;
};

typedef std::list<CatchStatement*> CatchStatements;


class ContinueStatement : public Statement
{
public:
	explicit ContinueStatement(const Token& token)
	: Statement(StatementType::ContinueStatement, token)
	{ }
};


class DeleteStatement : public Statement
{
public:
	explicit DeleteStatement(const Token& token, Node* exp)
	: Statement(StatementType::DeleteStatement, token),
	  mExpression(exp)
	{ }
	~DeleteStatement() {
		delete mExpression;
	}

public:
	Node* mExpression;
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


class ForeachStatement : public Statement
{
public:
	ForeachStatement(const Token& token, TypeDeclaration* typeDeclaration, Node* collectionExpression, MethodExpression* iteratorExpression,
					 MethodExpression* hasNextExpression, MethodExpression* nextExpression, Node* loopStatement)
	: Statement(StatementType::ForeachStatement, token),
	  mCollectionExpression(collectionExpression),
	  mGetIteratorExpression(iteratorExpression),
	  mHasNextExpression(hasNextExpression),
	  mNextExpression(nextExpression),
	  mStatement(loopStatement),
	  mTypeDeclaration(typeDeclaration)
	{ }
	~ForeachStatement() {
		delete mCollectionExpression;
		delete mGetIteratorExpression;
		delete mHasNextExpression;
		delete mNextExpression;
		delete mStatement;
		delete mTypeDeclaration;
	}

public:
	Node* mCollectionExpression;
	MethodExpression* mGetIteratorExpression;
	MethodExpression* mHasNextExpression;
	MethodExpression* mNextExpression;
	Node* mStatement;
	TypeDeclaration* mTypeDeclaration;
};


class ForStatement : public Statement
{
public:
	ForStatement(const Token& token, Node* initStatement, Node* condition, Node* iterationStatement, Node* loopStatement)
	: Statement(StatementType::ForStatement, token),
	  mCondition(condition),
	  mInitialization(initStatement),
	  mIteration(iterationStatement),
	  mStatement(loopStatement)
	{ }
	~ForStatement() {
		delete mCondition;
		delete mInitialization;
		delete mIteration;
		delete mStatement;
	}

public:
	Node* mCondition;
	Node* mInitialization;
	Node* mIteration;
	Node* mStatement;
};


class IfStatement : public Statement
{
public:
	IfStatement(const Token& token, Node* condition, Node* ifBlock, Node* elseBlock)
	: Statement(StatementType::IfStatement, token),
	  mCondition(condition),
	  mElseBlock(elseBlock),
	  mIfBlock(ifBlock)
	{ }
	~IfStatement() {
		delete mCondition;
		delete mElseBlock;
		delete mIfBlock;
	}

public:
	Node* mCondition;
	Node* mElseBlock;
	Node* mIfBlock;
};


class PrintStatement : public Statement
{
public:
	PrintStatement(const Token& token, Node* exp)
	: Statement(StatementType::PrintStatement, token),
	  mExpression(exp),
	  mPosition(token.position())
	{ }
	~PrintStatement() {
		delete mExpression;
	}

public:
	Node* mExpression;
	Common::Position mPosition;
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


class SwitchStatement : public Statement
{
public:
	SwitchStatement(const Token& token, Node* exp, const CaseStatements& caseStatements, Statements* defaultStatement)
	: Statement(StatementType::SwitchStatement, token),
	  mCaseStatements(caseStatements),
	  mDefaultStatement(defaultStatement),
	  mExpression(exp)
	{ }
	~SwitchStatement() {
		for ( CaseStatements::iterator it = mCaseStatements.begin(); it != mCaseStatements.end(); ++it ) {
			delete (*it);
		}
		delete mDefaultStatement;
		delete mExpression;
	}

public:
	CaseStatements mCaseStatements;
	Statements* mDefaultStatement;
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


class TryStatement : public Statement
{
public:
	TryStatement(const Token& token, Statements* tryBlock, const CatchStatements& catchStatements, Statements* finallyBlock)
	: Statement(StatementType::TryStatement, token),
	  mCatchStatements(catchStatements),
	  mFinallyBlock(finallyBlock),
	  mTryBlock(tryBlock)
	{ }
	~TryStatement() {
		for ( CatchStatements::iterator it = mCatchStatements.begin(); it != mCatchStatements.end(); ++it ) {
			delete (*it);
		}
		delete mFinallyBlock;
		delete mTryBlock;
	}

public:
	CatchStatements mCatchStatements;
	Statements* mFinallyBlock;
	Statements* mTryBlock;
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


class WhileStatement : public Statement
{
public:
	WhileStatement(const Token& token, Node* condition, Node* statement)
	: Statement(StatementType::WhileStatement, token),
	  mCondition(condition),
	  mStatement(statement)
	{ }
	~WhileStatement() {
		delete mCondition;
		delete mStatement;
	}

public:
	Node* mCondition;
	Node* mStatement;
};


}
}

#endif
