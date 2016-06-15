
// Header
#include "Node.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Node::Node()
: mInterpreter(0),
  mLeftNode(0),
  mMemory(0),
  mRightNode(0)
{
}

Node::~Node()
{
}

void Node::addLeft(Node *node)
{
	mLeftNode = node;
}

void Node::addRight(Node *node)
{
	mRightNode = node;
}

void Node::scope(const std::string& s)
{
	mScope = s;
}

const std::string& Node::scope() const
{
	return mScope;
}


}
}
