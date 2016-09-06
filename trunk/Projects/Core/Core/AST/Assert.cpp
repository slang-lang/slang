
// Header
#include "Assert.h"

// Library includes
#include <cassert>

// Project includes
#include <Common/Exceptions.h>
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
	mInterpreter->setTokens(mTokens);

	Runtime::Object result;
	mInterpreter->execute(&result);

	if ( !isTrue(result) ) {
		throw Utils::Exceptions::AssertionFailed(result.getValue(), mTokens.begin()->position());
	}

	return 0;
}

}
}
