
// Header
#include "Condition.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Condition::Condition(const TokenList& tokens)
{
	mTokens = tokens;
}

Node* Condition::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object result = mInterpreter->process();

	return 0;
}

}
}
