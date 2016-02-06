
// Header
#include "While.h"

// Library includes

// Project includes
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


While::While(const TokenList& tokens)
{
	mTokens = tokens;
}

Node* While::execute()
{
	mInterpreter->setTokens(mTokens);

	Runtime::Object condition;
	for ( ; ; ) {
		mInterpreter->execute(&condition);

		if ( !isTrue(condition) ) {
			break;
		}

		// execute body
	};

	return mLeftNode;
}


}
}
