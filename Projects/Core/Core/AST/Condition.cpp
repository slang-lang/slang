
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
	mInterpreter->setTokens(mTokens);

	Runtime::Object result;
	mInterpreter->execute(&result);

	return isTrue(result);
}

}
}
