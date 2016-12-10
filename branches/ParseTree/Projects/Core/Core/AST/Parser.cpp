
// Header
#include "Parser.h"

// Library includes

// Project includes
#include "Tree.h"

#include "Assert.h"
#include "Print.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Parser::Parser(const TokenList& tokens)
: mTokens(tokens),
  mTree(0)
{
	mCurrentToken = mTokens.begin();
}

Parser::~Parser()
{
}

Tree* Parser::buildTree()
{
	if ( mTree ) {
		delete mTree;
		mTree = 0;
	}

	mTree = new Tree();

	while ( mCurrentToken != mTokens.end() ) {
		mark();

		if ( !handleKeyword(mCurrentToken) ) {
			release();
		}

		consume();
	}

	return mTree;
}

bool Parser::consume()
{
	if ( mCurrentToken != mTokens.end() ) {
		mCurrentToken++;
		return true;
	}
	
	return false;
}

bool Parser::handleAssert(const TokenIterator& token)
{
	Assert *a = new Assert(TokenList());

	mTree->addNode(a);
	return true;
}

bool Parser::handleKeyword(const TokenIterator& token)
{
	if ( (*token).content() == "assert" ) {
		return handleAssert(token);
	}
	else if ( (*token).content() == "print" ) {
		return handlePrint(token);
	}

	return false;
}

bool Parser::handlePrint(const TokenIterator& token)
{
	Print *p = new Print(TokenList());

	mTree->addNode(p);
	return true;
}

void Parser::mark()
{
	mTmpToken = mCurrentToken;
}

void Parser::release()
{
	mCurrentToken = mTmpToken;
}


}
}
