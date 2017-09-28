
// Header
#include "NodeFactory.h"

// Library includes

// Project includes

// Namespace declarations



namespace ObjectiveScript {
namespace AST {


NodeFactory::NodeFactory()
: mCurrentID(0)
{
}

NodeFactory::~NodeFactory()
{
}

NodeID NodeFactory::nextID()
{
    return ++mCurrentID;
}

void NodeFactory::updateID(Node* node)
{
    assert( node );

    if ( node->getId() != DEFAULT_ID ) {
        // this node already has a valid ID set, this is perfectly okay as node-reuse is allowed
        return;
    }

    node->setId(nextID());
}


}
}
