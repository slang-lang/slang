
#ifndef ObjectiveScript_AST_Tree_h
#define ObjectiveScript_AST_Tree_h


#include "Node.h"


namespace ObjectiveScript {
namespace AST {


class Tree
{
public:
	Tree();
	~Tree();

public:
	void addNode(Node *node);

protected:

private:
	NodeList mNodes;
};



}
}


#endif
