
#ifndef ObjectiveScript_Core_AST_Expression_h
#define ObjectiveScript_Core_AST_Expression_h


// Library includes
#include <list>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/AtomicValue.h>
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class Expression : public Node
{
public:
	class ExpressionType {
	public:
		enum E {
			BinaryExpression,
			CopyExpression,
			LiteralExpression,
			MethodExpression,
			NewExpression,
			TypecastExpression,
			UnaryExpression,
			VariableExpression,
		};
	};

public:
	Expression(ExpressionType::E expressionType)
	: Node(NodeType::Expression),
	  mExpressionType(expressionType)
	{ }

	ExpressionType::E getExpressionType() const {
		return mExpressionType;
	}

protected:
	ExpressionType::E mExpressionType;
};

typedef Expression BooleanExpression;
typedef Expression Factor;
typedef std::list<Expression*> ExpressionList;


// Forward declarations
class VariableExpression;


///////////////////////////////////////////////////////////////////////////////
// Binary expressions

class BinaryExpression : public Expression
{
public:
	BinaryExpression(const Token& token, Expression* left, Expression* right)
	: Expression(ExpressionType::BinaryExpression),
	  mLeft(left),
	  mRight(right),
	  mToken(token)
	{ }

public:
	Expression* mLeft;
	Expression* mRight;
	Token mToken;
};


class UnaryExpression : public Expression
{
public:
	UnaryExpression(const Token& token, Expression* exp)
	: Expression(ExpressionType::UnaryExpression),
	  mExpression(exp),
	  mToken(token)
	{ }

public:
	Expression* mExpression;
	Token mToken;
};


// Binary expressions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Literal expressions

class LiteralExpression : public Expression
{
public:
	LiteralExpression(Runtime::AtomicValue value)
	: Expression(ExpressionType::LiteralExpression),
	  mValue(value)
	{ }

public:
	Runtime::AtomicValue mValue;
};


class BooleanLiteralExpression : public LiteralExpression
{
public:
	BooleanLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class DoubleLiteralExpression : public LiteralExpression
{
public:
	DoubleLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class FloatLiteralExpression : public LiteralExpression
{
public:
	FloatLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class IntegerLiteralExpression : public LiteralExpression
{
public:
	IntegerLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class StringLiteralExpression : public LiteralExpression
{
public:
	StringLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

// Literal expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Memory expressions

class CopyExpression : public Expression
{
public:
	CopyExpression(VariableExpression* exp)
	: Expression(ExpressionType::CopyExpression),
	  mExpression(exp)
	{ }

public:
	VariableExpression* mExpression;
};


class NewExpression : public Expression
{
public:
	NewExpression(VariableExpression* exp)
	: Expression(ExpressionType::NewExpression),
	  mExpression(exp)
	{ }

public:
	VariableExpression* mExpression;
};


// Memory expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Method expressions

class MethodExpression : public Expression
{
public:
	MethodExpression(const std::string& name, const ExpressionList& params)
	: Expression(ExpressionType::MethodExpression),
	  mName(name),
	  mParams(params)
	{ }

public:
	std::string mName;
	ExpressionList mParams;
};

// Method expressions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Variable expressions

class TypecastExpression : public Expression
{
public:
	TypecastExpression(const std::string& destinationType, Expression* exp)
	: Expression(ExpressionType::TypecastExpression),
	  mDestinationType(destinationType),
	  mExpression(exp)
	{ }

public:
	std::string mDestinationType;
	Expression* mExpression;
};

class VariableExpression : public Expression
{
public:
	VariableExpression(const std::string& name)
	: Expression(ExpressionType::VariableExpression),
	  mName(name)
	{ }

public:
	std::string mName;
};

// Variable expressions
///////////////////////////////////////////////////////////////////////////////



}
}

#endif
