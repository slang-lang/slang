
#ifndef ObjectiveScript_AST_Parser_h
#define ObjectiveScript_AST_Parser_h


// Library includes

// Project includes
#include <Core/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {

// Forward declarations
class Tree;

class Parser
{
public:
	Parser(const TokenList& tokens);
	~Parser();

public:
	Tree* buildTree();

protected:

private:
	bool handleKeyword(const TokenIterator& token);
	bool handleAssert(const TokenIterator& token);
	bool handlePrint(const TokenIterator& token);

private:
	bool consume();
	void mark();
	void release();

private:
	TokenIterator mCurrentToken;
	TokenList mTokens;
	TokenIterator mTmpToken;
	Tree *mTree;
};


}
}


#endif
