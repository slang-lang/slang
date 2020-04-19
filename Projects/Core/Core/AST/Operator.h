
#ifndef ObjectiveScript_Core_AST_Operator_h
#define ObjectiveScript_Core_AST_Operator_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>

#include <utility>
#include "Expression.h"
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace AST {


class Operator : public Node
{
public:
	class OperatorType {
	public:
		enum E {
			BinaryOperator,
			UnaryOperator
		};
	};

public:
	explicit Operator(OperatorType::E operatorType, Token token)
	: Node(NodeType::Operator),
	  mOperatorType(operatorType),
	  mToken(std::move(token))
	{ }

	OperatorType::E getOperatorType() const {
		return mOperatorType;
	}

	const Token& token() const {
		return mToken;
	}

private:
	OperatorType::E mOperatorType;
	Token mToken;
};


class BinaryOperator : public Operator
{
public:
	BinaryOperator(const Token& token, Expression* left, Expression* right)
	: Operator(OperatorType::BinaryOperator, token),
	  mLeft(left),
	  mRight(right)
	{ }
	~BinaryOperator() override {
		delete mLeft;
		delete mRight;
	}

public:
	Expression* mLeft;
	Expression* mRight;
};


class UnaryOperator : public Operator
{
public:
	UnaryOperator(const Token& token, Expression* exp)
	: Operator(OperatorType::UnaryOperator, token),
	  mExpression(exp)
	{ }
	~UnaryOperator() override {
		delete mExpression;
	}

public:
	Expression* mExpression;
};



}
}

#endif
