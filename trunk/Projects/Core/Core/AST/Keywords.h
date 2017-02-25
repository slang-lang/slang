
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
	AssertStatement(Node* exp, const Common::Position& position)
	: Statement(StatementType::AssertStatement),
	  mExpression(exp),
	  mPosition(position)
	{ }
	~AssertStatement() {
		if ( mExpression ) {
			delete mExpression;
		}
	}

public:
	Node* mExpression;
	Common::Position mPosition;
};


class CaseStatement : public Statement
{
public:
	CaseStatement(Node* caseExpression, Statements* caseBlock)
	: Statement(StatementType::CaseStatement),
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
	CatchStatement(TypeDeclaration* typeDeclaration, Statements* statements)
	: Statement(StatementType::CatchStatement),
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
	explicit DeleteStatement(Node* exp)
	: Statement(StatementType::DeleteStatement),
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
	ForeachStatement(TypeDeclaration* typeDeclaration, SymbolExpression* loopVariable, Node* loopStatement)
	: Statement(StatementType::ForeachStatement),
	  mLoopVariable(loopVariable),
	  mStatement(loopStatement),
	  mTypeDeclaration(typeDeclaration)
	{ }
	~ForeachStatement() {
		delete mLoopVariable;
		delete mStatement;
		delete mTypeDeclaration;
	}

public:
	SymbolExpression* mLoopVariable;
	Node* mStatement;
	TypeDeclaration* mTypeDeclaration;
};


class ForStatement : public Statement
{
public:
	ForStatement(Node* initStatement, Node* condition, Node* iterationStatement, Node* loopStatement)
	: Statement(StatementType::ForStatement),
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
	IfStatement(Node* exp, Node* ifBlock, Node* elseBlock)
	: Statement(StatementType::IfStatement),
	  mElseBlock(elseBlock),
	  mExpression(exp),
	  mIfBlock(ifBlock)
	{ }
	~IfStatement() {
		delete mElseBlock;
		delete mExpression;
		delete mIfBlock;
	}

public:
	Node* mElseBlock;
	Node* mExpression;
	Node* mIfBlock;
};


class PrintStatement : public Statement
{
public:
	PrintStatement(Node* exp, const Common::Position& position)
	: Statement(StatementType::PrintStatement),
	  mExpression(exp),
	  mPosition(position)
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
	SwitchStatement(Node* exp, const CaseStatements& caseStatements, Statements* defaultStatement)
	: Statement(StatementType::SwitchStatement),
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
	TryStatement(Statements* tryBlock, const CatchStatements& catchStatements, Statements* finallyBlock)
	: Statement(StatementType::TryStatement),
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
	WhileStatement(Node* condition, Node* statement)
	: Statement(StatementType::WhileStatement),
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