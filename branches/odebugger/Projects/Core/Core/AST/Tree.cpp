
// Header
#include "Tree.h"


namespace ObjectiveScript {
namespace AST {


Tree::Tree()
{
}

Tree::~Tree()
{
	for ( NodeList::iterator it = mNodes.begin(); it != mNodes.end(); ++it ) {
		delete (*it);
	}
}

void Tree::addNode(Node *node)
{
	if ( !node ) {
		return;
	}

	mNodes.push_back(node);
}


}
}
