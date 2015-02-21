
#ifndef AST_Condition_h
#define AST_Condition_h


// Library includes

// Project includes
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class Condition: public Node
{
public:
	Condition(const TokenList& tokens);

	Node* execute();
};


}
}


#endif
