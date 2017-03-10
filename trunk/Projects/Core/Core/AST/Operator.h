
#ifndef ObjectiveScript_Core_AST_Operator_h
#define ObjectiveScript_Core_AST_Operator_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include "Expression.h"
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
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
	explicit Operator(OperatorType::E operatorType)
	: Node(NodeType::Operator),
	  mOperatorType(operatorType)
	{ }

	OperatorType::E getOperatorType() const {
		return mOperatorType;
	}

private:
	OperatorType::E mOperatorType;
};


class BinaryOperator : public Operator
{
public:
	BinaryOperator(const Token& token, Expression* left, Expression* right)
	: Operator(OperatorType::BinaryOperator),
	  mLeft(left),
	  mRight(right),
	  mToken(token)
	{ }
	virtual ~BinaryOperator() {
		delete mLeft;
		delete mRight;
	}

public:
	Expression* mLeft;
	Expression* mRight;
	Token mToken;
};


class UnaryOperator : public Operator
{
public:
	UnaryOperator(const Token& token, Expression* exp)
	: Operator(OperatorType::UnaryOperator),
	  mExpression(exp),
	  mToken(token)
	{ }
	virtual ~UnaryOperator() {
		delete mExpression;
	}

public:
	Expression* mExpression;
	Token mToken;
};



}
}

#endif
