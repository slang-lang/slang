
#ifndef ObjectiveScript_Core_AST_NodeFactory_h
#define ObjectiveScript_Core_AST_NodeFactory_h


// Library includes

// Project includes
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class NodeFactory
{
public:
    NodeFactory();
    ~NodeFactory();

public:
    void updateID(Node* node);

private:
    NodeID nextID();

private:
    NodeID mCurrentID;
};


}
}


#endif
