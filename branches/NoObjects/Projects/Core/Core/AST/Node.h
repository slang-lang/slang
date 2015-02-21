
#ifndef AST_Node_h
#define AST_Node_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Interpreter.h>
#include <Core/Memory.h>
#include <Core/Token.h>

// Forward declarations

// Namespace declarations

namespace ObjectiveScript {
namespace AST {


// Forward declarations
class Node;


typedef std::list<Node*> NodeList;


class Node
{
public:
	Node();
	virtual ~Node();

public:
	virtual Node* execute() = 0;

public:
	void addLeft(Node *node);
	void addRight(Node *node);

	void scope(const std::string& s);
	const std::string& scope() const;

protected:
	Interpreter *mInterpreter;
	Node *mLeftNode;
	Memory *mMemory;
	//NodeList mNodes;
	Node *mRightNode;
	std::string mScope;
	TokenList mTokens;

private:

};


}
}


#endif
