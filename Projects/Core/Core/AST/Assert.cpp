
// Header
#include "Assert.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Assert::Assert(const TokenList& tokens)
{
	mTokens = tokens;
}

Node* Assert::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object result = mInterpreter->process();
	if ( isFalse(result) ) {
		throw Utils::AssertionFailed(result.value(), mTokens.begin()->position());
	}

	return 0;
}

}
}
