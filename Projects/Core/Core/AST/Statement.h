
#ifndef Slang_Core_Core_AST_Statement_h
#define Slang_Core_Core_AST_Statement_h


// Library includes
#include <list>
#include <utility>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
#include "Expression.h"
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace AST {


class Statement : public Node
{
public:
	class StatementType {
	public:
		enum E {
			AssertStatement,
			AssignmentStatement,
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
	explicit Statement(StatementType::E statementType, Token token)
	: Node(NodeType::Statement),
	  mStatementType(statementType),
	  mToken(std::move(token))
	{ }

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


class ControlFlowStatement : public Statement
{
public:
	explicit ControlFlowStatement(StatementType::E statementType, const Token& token)
	: Statement(statementType, token)
	{ }
};


class Statements : public Statement
{
public:
	typedef std::list<Node*> Nodes;

public:
	explicit Statements(const Token& token)
	: Statement(StatementType::Statements, token)
	{ }
	~Statements() override {
		for ( auto & mNode : mNodes ) {
			delete mNode;
		}
	}

public:
	Nodes mNodes;
};


class TypeDeclaration : public Statement
{
public:
	TypeDeclaration(const Token& token, std::string type, PrototypeConstraints constraints, std::string name, bool isConst, bool isReference, Expression* assignmentExp)
	: Statement(StatementType::TypeDeclaration, token),
	  mAssignmentExpression(assignmentExp),
	  mConstraints(std::move(constraints)),
	  mIsConst(isConst),
	  mIsReference(isReference),
	  mName(std::move(name)),
	  mType(std::move(type))
	{ }
	~TypeDeclaration() override {
		delete mAssignmentExpression;
	}

public:
	Expression* mAssignmentExpression;
	PrototypeConstraints mConstraints;
	bool mIsConst;
	bool mIsReference;
	std::string mName;
	std::string mType;
};


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


class AssertStatement : public Statement
{
public:
	AssertStatement(const Token& token, Node* exp, Node* message)
	: Statement(StatementType::AssertStatement, token),
	  mExpression(exp),
	  mMessage(message),
	  mPosition(token.position())
	{ }
	~AssertStatement() override {
		delete mExpression;
		delete mMessage;
	}

public:
	Node* mExpression;
	Node* mMessage;
	Common::Position mPosition;
};


class AssignmentStatement : public Statement
{
public:
	explicit AssignmentStatement( const Token& token, Node* left, Node* right )
	: Statement(StatementType::AssignmentStatement, token),
	  mLeftExpression(left),
	  mRightExpression(right)
	{ }
	~AssignmentStatement() override {
		delete mLeftExpression;
		delete mRightExpression;
	}

public:
	Node* mLeftExpression;
	Node* mRightExpression;
};


class BreakStatement : public ControlFlowStatement
{
public:
	explicit BreakStatement(const Token& token)
	: ControlFlowStatement(StatementType::BreakStatement, token)
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
	~CaseStatement() override {
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
	~CatchStatement() override {
		delete mStatements;
		delete mTypeDeclaration;
	}

public:
	Statements* mStatements;
	TypeDeclaration* mTypeDeclaration;
};

typedef std::list<CatchStatement*> CatchStatements;


class ContinueStatement : public ControlFlowStatement
{
public:
	explicit ContinueStatement(const Token& token)
	: ControlFlowStatement(StatementType::ContinueStatement, token)
	{ }
};


class DeleteStatement : public Statement
{
public:
	explicit DeleteStatement(const Token& token, Node* exp)
	: Statement(StatementType::DeleteStatement, token),
	  mExpression(exp)
	{ }
	~DeleteStatement() override {
		delete mExpression;
	}

public:
	Node* mExpression;
};


class ExitStatement : public ControlFlowStatement
{
public:
	explicit ExitStatement(const Token& token, Node* exp)
	: ControlFlowStatement(StatementType::ExitStatement, token),
	  mExpression(exp)
	{ }
	~ExitStatement() override {
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
	~ForeachStatement() override {
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
	~ForStatement() override {
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
	~IfStatement() override {
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
	~PrintStatement() override {
		delete mExpression;
	}

public:
	Node* mExpression;
	Common::Position mPosition;
};


class ReturnStatement : public ControlFlowStatement
{
public:
	explicit ReturnStatement(const Token& token, Node* exp)
	: ControlFlowStatement(StatementType::ReturnStatement, token),
	  mExpression(exp)
	{ }
	~ReturnStatement() override {
		delete mExpression;
	}

public:
	Node* mExpression;
};


class SwitchStatement : public Statement
{
public:
	SwitchStatement(const Token& token, Node* exp, CaseStatements caseStatements, Statements* defaultStatement)
	: Statement(StatementType::SwitchStatement, token),
	  mCaseStatements(std::move(caseStatements)),
	  mDefaultStatement(defaultStatement),
	  mExpression(exp)
	{ }
	~SwitchStatement() override {
		for ( auto& mCaseStatement : mCaseStatements ) {
			delete mCaseStatement;
		}
		delete mDefaultStatement;
		delete mExpression;
	}

public:
	CaseStatements mCaseStatements;
	Statements* mDefaultStatement;
	Node* mExpression;
};


class ThrowStatement : public ControlFlowStatement
{
public:
	explicit ThrowStatement(const Token& token, Node* exp)
	: ControlFlowStatement(StatementType::ThrowStatement, token),
	  mExpression(exp)
	{ }
	~ThrowStatement() override {
		delete mExpression;
	}

public:
	Node* mExpression;
};


class TryStatement : public Statement
{
public:
	TryStatement(const Token& token, Statements* tryBlock, CatchStatements catchStatements, Statements* finallyBlock)
	: Statement(StatementType::TryStatement, token),
	  mCatchStatements(std::move(catchStatements)),
	  mFinallyBlock(finallyBlock),
	  mTryBlock(tryBlock)
	{ }
	~TryStatement() override {
		for ( auto& mCatchStatement : mCatchStatements ) {
			delete mCatchStatement;
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
	TypeInference(const Token& token, const std::string& type, const PrototypeConstraints& constraints, const std::string& name, bool isConst, bool isReference, Expression* assignmentExp)
	: TypeDeclaration(token, type, constraints, name, isConst, isReference, assignmentExp)
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
	~WhileStatement() override {
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
