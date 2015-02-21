
#ifndef AST_While
#define AST_While


#include "Node.h"


namespace ObjectiveScript {
namespace AST {


class While : public Node
{
public:
	While(const TokenList& tokens);

	Node* execute();

protected:

private:

};


}
}


#endif
