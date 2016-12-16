
#ifndef ObjectiveScript_Core_AST_Node_h
#define ObjectiveScript_Core_AST_Node_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


class Node
{
public:
	class NodeType {
	public:
		enum E {
			Expression,
			Operator,
			Statement
		};
	};

public:
	explicit Node(NodeType::E type)
	: mType(type)
	{ }
	virtual ~Node() { }

	NodeType::E getNodeType() const {
		return mType;
	}

protected:
	NodeType::E mType;
};


}
}


#endif
