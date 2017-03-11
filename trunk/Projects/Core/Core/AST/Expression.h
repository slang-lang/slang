
#ifndef ObjectiveScript_Core_AST_Expression_h
#define ObjectiveScript_Core_AST_Expression_h


// Library includes
#include <list>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Scope.h>
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
			IsExpression,
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
	virtual ~Expression() { }

	ExpressionType::E getExpressionType() const {
		return mExpressionType;
	}

	const std::string& getResultType() const {
		return mResultType;
	}

protected:
	ExpressionType::E mExpressionType;
	std::string mResultType;
};

typedef std::list<Node*> ExpressionList;


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
	explicit BinaryExpression(Node* left, const Token& operation, Node* right, const std::string& resultType)
	: Expression(ExpressionType::BinaryExpression),
	  mLeft(left),
	  mOperation(operation),
	  mRight(right),
	  mBinaryExpressionType(BinaryExpressionType::GenericBinaryExpression)
	{
		mResultType = resultType;
	}
	virtual ~BinaryExpression() {
		delete mLeft;
		delete mRight;
	}

	BinaryExpressionType::E getBinaryExpressionType() const {
		return mBinaryExpressionType;
	}

public:
	Node* mLeft;
	Token mOperation;
	Node* mRight;

protected:
	BinaryExpressionType::E mBinaryExpressionType;
};


class BooleanBinaryExpression : public BinaryExpression
{
public:
	explicit BooleanBinaryExpression(Node* left, const Token& operation, Node* right)
	: BinaryExpression(left, operation, right, "bool")
	{
		mBinaryExpressionType = BinaryExpressionType::BooleanBinaryExpression;
	}
};

// Binary expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Unary expressions

class UnaryExpression : public Expression
{
public:
	explicit UnaryExpression(const Token& operation, Node* exp)
	: Expression(ExpressionType::UnaryExpression),
	  mExpression(exp),
	  mOperation(operation)
	{
		mResultType = static_cast<Expression*>(exp)->getResultType();
	}
	virtual ~UnaryExpression() {
		delete mExpression;
	}

public:
	Node* mExpression;
	Token mOperation;
};


class BooleanUnaryExpression : public Expression
{
public:
	explicit BooleanUnaryExpression(const Token& operation, Node* exp)
	: Expression(ExpressionType::UnaryExpression),
	  mExpression(exp),
	  mOperation(operation)
	{
		// TODO: use BoolObject::TYPENAME
		mResultType = "bool";
	}
	virtual ~BooleanUnaryExpression() {
		delete mExpression;
	}

public:
	Node* mExpression;
	Token mOperation;
};

// Unary expressions
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
	{
		// TODO: use BoolObject::TYPENAME
		mResultType = "bool";
	}
};


class DoubleLiteralExpression : public LiteralExpression
{
public:
	explicit DoubleLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		// TODO: use DoubleObject::TYPENAME
		mResultType = "double";
	}
};


class FloatLiteralExpression : public LiteralExpression
{
public:
	explicit FloatLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		// TODO: use FloatObject::TYPENAME
		mResultType = "float";
	}
};


class IntegerLiteralExpression : public LiteralExpression
{
public:
	explicit IntegerLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		// TODO: use IntegerObject::TYPENAME
		mResultType = "int";
	}
};


class StringLiteralExpression : public LiteralExpression
{
public:
	explicit StringLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		// TODO: use StringObject::TYPENAME
		mResultType = "string";
	}
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
	~CopyExpression() {
		delete mExpression;
	}

public:
	Node* mExpression;
};


class NewExpression : public Expression
{
public:
	explicit NewExpression(const std::string& type, Node* exp)
	: Expression(ExpressionType::NewExpression),
	  mExpression(exp),
	  mType(type)
	{
		mResultType = type;
	}
	~NewExpression() {
		delete mExpression;
	}

public:
	Node* mExpression;
	std::string mType;
};

// Memory expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Symbol expressions

class IsExpression : public Expression
{
public:
	explicit IsExpression(Node* expression, const std::string& matchType)
	: Expression(ExpressionType::IsExpression),
	  mExpression(expression),
	  mMatchType(matchType)
	{
		// TODO: use BoolObject::TYPENAME
		mResultType = "bool";
	}

public:
	Node* mExpression;
	std::string mMatchType;
};


class SymbolExpression : public Expression
{
public:
	explicit SymbolExpression(const std::string& name, const std::string& resultType, SymbolExpression* symbolExpression)
	: Expression(ExpressionType::SymbolExpression),
	  mName(name),
	  mSurroundingScope(0),
	  mSymbolExpression(symbolExpression)
	{
		// retrieve return type from sub-expression
		mResultType = symbolExpression ? symbolExpression->getResultType() : resultType;
	}
	~SymbolExpression() {
		delete mSymbolExpression;
	}

	std::string toString() const {
		std::string result = mName;

		if ( mSymbolExpression ) {
			result += "." + mSymbolExpression->toString();
		}

		return result;
	}

public:
	std::string mName;
	IScope* mSurroundingScope;
	SymbolExpression* mSymbolExpression;
};


class TypecastExpression : public Expression
{
public:
	explicit TypecastExpression(const std::string& destinationType, Node* exp)
	: Expression(ExpressionType::TypecastExpression),
	  mDestinationType(destinationType),
	  mExpression(exp)
	{
		mResultType = mDestinationType;
	}
	~TypecastExpression() {
		delete mExpression;
	}

public:
	std::string mDestinationType;
	Node* mExpression;
};


class TypeidExpression : public Expression
{
public:
	explicit TypeidExpression(Node* expression)
	: Expression(ExpressionType::TypeidExpression),
	  mExpression(expression)
	{
		// TODO: use StringObject::TYPENAME
		mResultType = "string";
	}
	~TypeidExpression() {
		delete mExpression;
	}

public:
	Node* mExpression;
};

// Variable expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Method expressions

class MethodExpression : public Expression
{
public:
	explicit MethodExpression(SymbolExpression* symbol, const ExpressionList& params, const std::string& resultType)
	: Expression(ExpressionType::MethodExpression),
	  mParams(params),
	  mSymbol(symbol)
	{
		// due to the possibility of method overloading we cannot use the result type of our symbol
		mResultType = resultType;
	}
	~MethodExpression() {
		for ( ExpressionList::iterator it = mParams.begin(); it != mParams.end(); ++it ) {
			delete (*it);
		}
		delete mSymbol;
	}

public:
	ExpressionList mParams;
	SymbolExpression* mSymbol;
};

// Method expressions
///////////////////////////////////////////////////////////////////////////////


}
}

#endif
