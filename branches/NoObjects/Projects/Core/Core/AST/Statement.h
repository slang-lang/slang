
#ifndef AST_Statement_h
#define AST_Statement_h


#include "Node.h"


namespace ObjectiveScript {


class Statement : public Node
{
public:
	Statement(const TokenList& tokens);

	void execute();
};


}


#endif
