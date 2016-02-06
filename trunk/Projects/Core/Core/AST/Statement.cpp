
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
	mInterpreter->setTokens(mTokens);

	Runtime::Object result;
	mInterpreter->execute(&result);

	return 0;
}


}
}
