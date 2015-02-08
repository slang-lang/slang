
#ifndef AST_While
#define AST_While


#include "Node.h"


namespace ObjectiveScript {


class While : public Node
{
public:
	While(const TokenList& tokens);

	void addNode(Node *node);

	void execute();

private:
	NodeList mNodes;
};


}


#endif
