
#ifndef AST_Statement_h
#define AST_Statement_h


#include "Node.h"


namespace ObjectiveScript {
namespace AST {


class Statement : public Node
{
public:
	Statement(const TokenList& tokens);

	Node* execute();
};


}
}


#endif
