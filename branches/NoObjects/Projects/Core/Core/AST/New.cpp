
// Header
#include "New.h"


namespace ObjectiveScript {


New::New(const TokenList& tokens)
{
	mTokens = tokens;
}

void New::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object result = mInterpreter->process();

}

}
