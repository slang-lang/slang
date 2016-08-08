
#ifndef ObjectiveScript_Parser_Parser_h
#define ObjectiveScript_Parser_Parser_h


// Library includes

// Project includes
#include <Core/Parameter.h>
#include <Core/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


bool checkSyntax(TokenIterator foundIt, const TokenList &expected);


class Parser
{
public:
	static TokenList collectScopeTokens(TokenIterator& token);

	static bool isInterfaceDeclaration(TokenIterator start);
	static bool isLibraryReference(TokenIterator start);
	static bool isLocalDeclaration(TokenIterator start);
	static bool isMemberDeclaration(TokenIterator start);
	static bool isMemberDeclarationWithModifier(TokenIterator start);
	static bool isMethodDeclaration(TokenIterator start);
	static bool isNamespaceDeclaration(TokenIterator start);
	static bool isObjectDeclaration(TokenIterator start);
	static bool isParameterDeclaration(TokenIterator start);
	static bool isPrototypeDeclaration(TokenIterator start);
	static bool isStructorDeclaration(TokenIterator start);

	static ParameterList parseParameters(TokenIterator &token);
};


}


#endif
