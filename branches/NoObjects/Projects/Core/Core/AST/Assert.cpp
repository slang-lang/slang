
// Header
#include "Assert.h"

#include <cassert>

#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>


namespace ObjectiveScript {


Assert::Assert(const TokenList& tokens)
{
	mTokens = tokens;
}

void Assert::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object result = mInterpreter->process();
	if ( isFalse(result) ) {
		throw Utils::AssertionFailed(result.value(), mTokens.begin()->position());
	}
}

}
