
// Header
#include "Print.h"


namespace ObjectiveScript {


Print::Print(const TokenList& tokens)
{
	mTokens = tokens;
}

void Print::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object result = mInterpreter->process();
	//Printer::print(result.value());
}


}
