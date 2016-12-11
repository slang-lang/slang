
#ifndef ObjectiveScript_Core_AST_Operator_h
#define ObjectiveScript_Core_AST_Operator_h


#include "Node.h"


namespace ObjectiveScript {
namespace AST {


class Operator : public Node
{
public:
	Operator()
	: Node(NodeType::Operator)
	{ }
};


}
}

#endif
