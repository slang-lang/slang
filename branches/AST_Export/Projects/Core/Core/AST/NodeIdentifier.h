
#ifndef ObjectiveScript_Core_AST_NodeIdentifier_h
#define ObjectiveScript_Core_AST_NodeIdentifier_h


// Library includes
#include <set>

// Project includes
#include "NodeFactory.h"
#include "TreeVisitor.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class NodeIdentifier : public ATreeVisitor,
					   private NodeFactory
{
public:
	NodeIdentifier();
	~NodeIdentifier();

public:
	void visit(Node* node);

private:
	typedef std::set<Node*> NodeSet;

private:
	NodeSet mNodes;
};


}
}


#endif
