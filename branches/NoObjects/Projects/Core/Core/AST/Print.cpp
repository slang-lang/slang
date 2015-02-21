
// Header
#include "Print.h"


namespace ObjectiveScript {
namespace AST {


Print::Print(const TokenList& tokens)
{
	mTokens = tokens;
}

Node* Print::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	Object result = mInterpreter->process();
	//Printer::print(result.value());

	return 0;
}


}
}
