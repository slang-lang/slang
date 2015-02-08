
// Header
#include "While.h"

#include <Core/Tools.h>


namespace ObjectiveScript {


While::While(const TokenList& tokens)
{
	mTokens = tokens;
}

void While::addNode(Node *node)
{
	mNodes.push_back(node);
}

void While::execute()
{
	mInterpreter->setScope(mScope);
	mInterpreter->setTokens(mTokens);

	while ( isTrue(mInterpreter->process()) ) {
		for ( NodeList::iterator it = mNodes.begin(); it != mNodes.end(); ++it ) {
			(*it)->execute();
		}
	}
}


}
