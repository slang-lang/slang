
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
			SymbolExpression,
			TypecastExpression,
			TypeidExpression,
			UnaryExpression
		};
	};

public:
	explicit Expression(ExpressionType::E expressionType)
	: Node(NodeType::Expression),
	  mExpressionType(expressionType)
	{ }

	ExpressionType::E getExpressionType() const {
		return mExpressionType;
	}

protected:
	ExpressionType::E mExpressionType;
};

typedef std::list<Node*> ExpressionList;


// Forward declarations
class SymbolExpression;


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
	explicit BinaryExpression(const Token& token, Node* left, Node* right)
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
	explicit BooleanBinaryExpression(const Token& token, Node* left, Node* right)
	: BinaryExpression(token, left, right)
	{
		mBinaryExpressionType = BinaryExpressionType::BooleanBinaryExpression;
	}
};


class UnaryExpression : public Expression
{
public:
	explicit UnaryExpression(const Token& token, Node* exp)
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
	explicit LiteralExpression(Runtime::AtomicValue value)
	: Expression(ExpressionType::LiteralExpression),
	  mValue(value)
	{ }

public:
	Runtime::AtomicValue mValue;
};


class BooleanLiteralExpression : public LiteralExpression
{
public:
	explicit BooleanLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class DoubleLiteralExpression : public LiteralExpression
{
public:
	explicit DoubleLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class FloatLiteralExpression : public LiteralExpression
{
public:
	explicit FloatLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class IntegerLiteralExpression : public LiteralExpression
{
public:
	explicit IntegerLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{ }
};

class StringLiteralExpression : public LiteralExpression
{
public:
	explicit StringLiteralExpression(Runtime::AtomicValue value)
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
	explicit CopyExpression(Node* exp)
	: Expression(ExpressionType::CopyExpression),
	  mExpression(exp)
	{ }

public:
	Node* mExpression;
};


class NewExpression : public Expression
{
public:
	explicit NewExpression(Symbol* symbol, Node* exp)
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
	explicit MethodExpression(SymbolExpression* symbol, const ExpressionList& params)
	: Expression(ExpressionType::MethodExpression),
	  mParams(params),
	  mSymbol(symbol)
	{ }

public:
	ExpressionList mParams;
	SymbolExpression* mSymbol;
};

// Method expressions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Symbol expressions

class SymbolExpression : public Expression
{
public:
	explicit SymbolExpression(const Token& name)
	: Expression(ExpressionType::SymbolExpression),
	  mName(name),
	  mScope(0)
	{ }

	std::string toString() const {
		std::string result = mName.content();

		if ( mScope ) {
			result += "." + mScope->toString();
		}

		return result;
	}

public:
	Token mName;
	SymbolExpression* mScope;
};


class TypecastExpression : public Expression
{
public:
	explicit TypecastExpression(const Token& destinationType, Node* exp)
	: Expression(ExpressionType::TypecastExpression),
	  mDestinationType(destinationType),
	  mExpression(exp)
	{ }

public:
	Token mDestinationType;
	Node* mExpression;
};


class TypeidExpression : public Expression
{
public:
	explicit TypeidExpression(Node* expression)
	: Expression(ExpressionType::TypeidExpression),
	  mExpression(expression)
	{ }

public:
	Node* mExpression;
};

// Variable expressions
///////////////////////////////////////////////////////////////////////////////



}
}

#endif
