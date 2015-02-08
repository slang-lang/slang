
// Header
#include "Node.h"


namespace ObjectiveScript {


Node::Node()
: mInterpreter(0),
  mMemory(0)
{
}

Node::~Node()
{
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
