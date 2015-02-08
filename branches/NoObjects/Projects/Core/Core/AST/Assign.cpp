
// Header
#include "Assign.h"


namespace ObjectiveScript {


Assign::Assign(const std::string& assignee, const TokenList& tokens)
: mAssignee(assignee)
{
	mTokens = tokens;
}

void Assign::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object *assignee = mMemory->getObject(mAssignee);
	assignee->assign(mInterpreter->process());
}


}
