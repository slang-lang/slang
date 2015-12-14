
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
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	/*Object result = */mInterpreter->process();
	return 0;
}


}
}
