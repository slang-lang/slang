
#ifndef AST_Assign_h
#define AST_Assign_h


#include "Node.h"


namespace ObjectiveScript {


class Assign : public Node
{
public:
	Assign(const std::string& assignee, const TokenList& tokens);

	void execute();

private:
	std::string mAssignee;
};


}


#endif
