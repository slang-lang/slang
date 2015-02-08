
#ifndef AST_Assert_h
#define AST_Assert_h


#include "Node.h"


namespace ObjectiveScript {


class Assert: public Node
{
public:
	Assert(const TokenList& tokens);

	void execute();
};


}


#endif
