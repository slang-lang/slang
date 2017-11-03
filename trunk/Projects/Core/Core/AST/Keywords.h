
#ifndef ObjectiveScript_Core_Core_AST_Keywords_h
#define ObjectiveScript_Core_Core_AST_Keywords_h


// Library includes

// Project includes
#include <Core/Common/Position.h>
#include "Statement.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


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


class ForeachStatement : public Statement
{
public:
	ForeachStatement(const Token& token, TypeDeclaration* typeDeclaration, Node* loopExpression, Node* loopStatement)
	: Statement(StatementType::ForeachStatement, token),
	  mLoopExpression(loopExpression),
	  mStatement(loopStatement),
	  mTypeDeclaration(typeDeclaration)
	{ }
	~ForeachStatement() {
		delete mLoopExpression;
		delete mStatement;
		delete mTypeDeclaration;
	}

public:
	Node* mLoopExpression;
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