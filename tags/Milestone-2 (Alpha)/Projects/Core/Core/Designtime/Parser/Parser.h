
#ifndef ObjectiveScript_Designtime_Parser_Parser_h
#define ObjectiveScript_Designtime_Parser_Parser_h


// Library includes

// Project includes
#include <Core/Attributes/ImplementationType.h>
#include <Core/Attributes/LanguageFeatureState.h>
#include <Core/Attributes/ObjectType.h>
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
	static std::string identify(TokenIterator& start);

	static ImplementationType::E parseImplementationType(TokenIterator& token, ImplementationType::E defaultValue);
	static LanguageFeatureState::E parseLanguageFeatureState(TokenIterator& token, LanguageFeatureState::E defaultValue);
	static ObjectType::E parseObjectType(TokenIterator& token);

	static bool isEnumDeclaration(TokenIterator start);
	static bool isInterfaceDeclaration(TokenIterator start);
	static bool isLibraryReference(TokenIterator start);
	static bool isLocalDeclaration(TokenIterator start);
	static bool isMemberDeclaration(TokenIterator start);
	static bool isMemberDeclarationWithModifier(TokenIterator start);
	static bool isMethodDeclaration(TokenIterator start);
	static bool isNamespaceDeclaration(TokenIterator start);
	static bool isObjectDeclaration(TokenIterator start);
	static bool isPrototypeDeclaration(TokenIterator start);
	static bool isStructorDeclaration(TokenIterator start);

	static ParameterList parseParameters(TokenIterator &token);
};


}


#endif
