
// Header
#include "Statement.h"


namespace ObjectiveScript {
namespace AST {


Statement::Statement(const TokenList& tokens)
{
	mTokens = tokens;
}

Node* Statement::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	mInterpreter->process();

	return 0;
}


}
}
