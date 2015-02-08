
#ifndef AST_New_h
#define AST_New_h


#include "Node.h"


namespace ObjectiveScript {


class New: public Node
{
public:
	New(const TokenList& tokens);

	void execute();
};


}


#endif
