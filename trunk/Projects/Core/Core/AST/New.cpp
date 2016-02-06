
// Header
#include "New.h"


namespace ObjectiveScript {
namespace AST {


New::New(const TokenList& tokens)
{
	mTokens = tokens;
}

Node* New::execute()
{
	mInterpreter->setTokens(mTokens);

	Runtime::Object result;
	mInterpreter->execute(&result);
	return 0;
}


}
}
