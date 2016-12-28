
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

public:
	Node* mExpression;
	Common::Position mPosition;
};


class CaseStatement : public Statement
{
public:
	CaseStatement(Node* caseExpression, Node* caseBlock)
	: Statement(StatementType::CaseStatement),
	  mCaseBlock(caseBlock),
	  mCaseExpression(caseExpression)
	{ }

public:
	Node* mCaseBlock;
	Node* mCaseExpression;
};

typedef std::list<CaseStatement*> CaseStatements;

class CatchStatement : public Statement
{
public:
	CatchStatement(TypeDeclaration* typeDeclaration, Node* statement)
	: Statement(StatementType::CatchStatement),
	  mStatement(statement),
	  mTypeDeclaration(typeDeclaration)
	{ }

public:
	Node* mStatement;
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

public:
	Node* mExpression;
};


class ForeachStatement : public Statement
{
public:
	ForeachStatement(TypeDeclaration* typeDeclaration, const Token& loopVariable, Node* loopStatement)
	: Statement(StatementType::ForeachStatement),
	  mLoopVariable(loopVariable),
	  mStatement(loopStatement),
	  mTypeDeclaration(typeDeclaration)
	{ }

public:
	Token mLoopVariable;
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

public:
	Node* mExpression;
	Common::Position mPosition;
};


class SwitchStatement : public Statement
{
public:
	SwitchStatement(Node* exp, const CaseStatements& caseStatements, Node* defaultStatement)
	: Statement(StatementType::SwitchStatement),
	  mCaseStatements(caseStatements),
	  mDefaultStatement(defaultStatement),
	  mExpression(exp)
	{ }

public:
	CaseStatements mCaseStatements;
	Node* mDefaultStatement;
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

public:
	CatchStatements mCatchStatements;
	Statements* mFinallyBlock;
	Statements* mTryBlock;
};


class WhileStatement : public Statement
{
public:
	WhileStatement(Node* condition, Node* statements)
	: Statement(StatementType::WhileStatement),
	  mExpression(condition),
	  mStatements(statements)
	{ }

public:
	Node* mExpression;
	Node* mStatements;
};


}
}


#endif