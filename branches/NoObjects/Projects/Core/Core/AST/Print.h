
#ifndef AST_Print_h
#define AST_Print_h


#include "Node.h"


namespace ObjectiveScript {


class Print: public Node
{
public:
	Print(const TokenList& tokens);

public:
	void execute();

public:

private:

};


}


#endif
