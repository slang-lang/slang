
#ifndef AST_Assert_h
#define AST_Assert_h


// Library includes

// Project includes
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class Assert: public Node
{
public:
	Assert(const TokenList& tokens);

	Node* execute();
};


}
}


#endif
