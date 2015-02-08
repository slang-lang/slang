
// Header
#include "Statement.h"


namespace ObjectiveScript {


Statement::Statement(const TokenList& tokens)
{
	mTokens = tokens;
}

void Statement::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	mInterpreter->process();
}


}
