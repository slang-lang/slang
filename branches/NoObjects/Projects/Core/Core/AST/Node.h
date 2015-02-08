
#ifndef AST_Node_h
#define AST_Node_h


#include <list>
#include <string>

#include <Core/Interpreter.h>
#include <Core/Memory.h>
#include <Core/Token.h>


namespace ObjectiveScript {


class Node
{
public:
	Node();
	virtual ~Node();

public:
	void scope(const std::string& s);
	const std::string& scope() const;

	virtual void execute() = 0;

protected:
	Interpreter *mInterpreter;
	Memory *mMemory;
	std::string mScope;
	TokenList mTokens;

private:

};

typedef std::list<Node*> NodeList;


}


#endif
