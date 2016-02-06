
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
	mInterpreter->setTokens(mTokens);

	Runtime::Object result;
	mInterpreter->execute(&result);
	//Printer::print(result.value());

	return 0;
}


}
}
