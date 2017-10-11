

// Header
#include "NodeIdentifier.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


NodeIdentifier::NodeIdentifier()
{
}

NodeIdentifier::~NodeIdentifier()
{
}

void NodeIdentifier::visit(Node* node)
{
	if ( !node ) {
		return;
	}

	updateID(node);

	mNodes.insert(node);

	ATreeVisitor::visit(node);
}


}
}
