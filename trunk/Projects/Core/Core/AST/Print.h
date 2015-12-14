
#ifndef AST_Print_h
#define AST_Print_h


#include "Node.h"


namespace ObjectiveScript {
namespace AST {


class Print: public Node
{
public:
	Print(const TokenList& tokens);

	Node* execute();
};


}
}


#endif
