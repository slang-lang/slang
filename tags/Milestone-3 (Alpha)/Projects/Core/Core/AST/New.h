
#ifndef AST_New_h
#define AST_New_h


#include "Node.h"


namespace ObjectiveScript {
namespace AST {


class New: public Node
{
public:
	New(const TokenList& tokens);

	Node* execute();
};


}
}


#endif
