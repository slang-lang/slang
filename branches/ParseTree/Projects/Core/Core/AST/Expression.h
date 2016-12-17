
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
typedef std::list<Node*> ExpressionList;


// Forward declarations
class VariableExpression;


///////////////////////////////////////////////////////////////////////////////
// Binary expressions

class BinaryExpression : public Expression
{
public:
	class BinaryExpressionType {
	public:
		enum E {
			BooleanBinaryExpression,
			GenericBinaryExpression
		};
	};

public:
	BinaryExpression(const Token& token, Node* left, Node* right)
	: Expression(ExpressionType::BinaryExpression),
	  mLeft(left),
	  mRight(right),
	  mToken(token),
	  mBinaryExpressionType(BinaryExpressionType::GenericBinaryExpression)
	{ }

	BinaryExpressionType::E getBinaryExpressionType() const {
		return mBinaryExpressionType;
	}

public:
	Node* mLeft;
	Node* mRight;
	Token mToken;

protected:
	BinaryExpressionType::E mBinaryExpressionType;
};

class BooleanBinaryExpression : public BinaryExpression
{
public:
	BooleanBinaryExpression(const Token& token, Node* left, Node* right)
	: BinaryExpression(token, left, right)
	{
		mBinaryExpressionType = BinaryExpressionType::BooleanBinaryExpression;
	}
};


class UnaryExpression : public Expression
{
public:
	UnaryExpression(const Token& token, Node* exp)
	: Expression(ExpressionType::UnaryExpression),
	  mExpression(exp),
	  mToken(token)
	{ }

public:
	Node* mExpression;
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
	CopyExpression(Node* exp)
	: Expression(ExpressionType::CopyExpression),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class NewExpression : public Expression
{
public:
	NewExpression(Symbol* symbol, Node* exp)
	: Expression(ExpressionType::NewExpression),
	  mExpression(exp),
	  mSymbol(symbol)
	{ }

public:
	Node* mExpression;
	Symbol* mSymbol;
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
	TypecastExpression(const std::string& destinationType, Node* exp)
	: Expression(ExpressionType::TypecastExpression),
	  mDestinationType(destinationType),
	  mExpression(exp)
	{ }

public:
	std::string mDestinationType;
	Node* mExpression;
};

class VariableExpression : public Expression
{
public:
	VariableExpression(const Token& name)
	: Expression(ExpressionType::VariableExpression),
	  mName(name)
	{ }

public:
	Token mName;
};

// Variable expressions
///////////////////////////////////////////////////////////////////////////////



}
}

#endif
