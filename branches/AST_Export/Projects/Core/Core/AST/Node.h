
#ifndef ObjectiveScript_Core_AST_Node_h
#define ObjectiveScript_Core_AST_Node_h


// Library includes
#include <cassert>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


typedef unsigned int NodeID;
const NodeID DEFAULT_ID = ~0;


class Node
{
public:
	class NodeType {
	public:
		enum E {
			Expression = 0,
			Operator,
			Statement
		};
	};

public:
	explicit Node(NodeType::E type)
	: mId(DEFAULT_ID),
	  mType(type)
	{ }
	virtual ~Node() { }

public:
	NodeID getId() const {
		return mId;
	}
	void setId(NodeID id) {
		assert( mId == DEFAULT_ID );
		mId = id;
	}

	NodeType::E getNodeType() const {
		return mType;
	}

protected:
	NodeID mId;
	NodeType::E mType;
};


}
}


#endif
