
#ifndef ObjectiveScript_Core_AST_BinaryOperator_h
#define ObjectiveScript_Core_AST_BinaryOperator_h


#include <Core/Designtime/Parser/Token.h>
#include "Expression.h"
#include "Operator.h"


namespace ObjectiveScript {
namespace AST {

// Forward declarations
//class Expression;

class BinaryOperator : public Operator
{
public:
	BinaryOperator(const Token& token, Expression* left, Expression* right)
	: mLeft(left),
	  mRight(right),
	  mToken(token)
	{ }

public:
	Expression* mLeft;
	Expression* mRight;
	Token mToken;
};


}
}

#endif
