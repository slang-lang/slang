
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
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	while ( isTrue(mInterpreter->process()) ) {
/*
		for ( NodeList::iterator it = mNodes.begin(); it != mNodes.end(); ++it ) {
			(*it)->execute();
		}
*/
	}

	return mLeftNode;
}


}
}
