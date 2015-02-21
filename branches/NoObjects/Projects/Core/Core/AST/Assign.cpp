
// Header
#include "Assign.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Token.h>

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Assign::Assign(const std::string& assignee, const TokenList& tokens)
: mAssignee(assignee)
{
	mTokens = tokens;
}

Node* Assign::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object *assignee = mMemory->getObject(mAssignee);
	if ( !assignee ) {
		// ups..
		throw Utils::NullPointerException("while trying to access " + mAssignee, (*mTokens.begin()).position());
	}

	// find out if this object is const
	if ( assignee->isConst() ) {
		throw Utils::ConstCorrectnessViolated("Not allowed to assign value to const object!", (*mTokens.begin()).position());
	}

	// TODO: find out if we are changing a member in a const method


	assignee->assign(mInterpreter->process());

	return 0;
}


}
}
