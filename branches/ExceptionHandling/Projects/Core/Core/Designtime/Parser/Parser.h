
#ifndef ObjectiveScript_Designtime_Parser_Parser_h
#define ObjectiveScript_Designtime_Parser_Parser_h


// Library includes

// Project includes
#include <Core/Attributes/ImplementationType.h>
#include <Core/Attributes/LanguageFeatureState.h>
#include <Core/Attributes/ObjectType.h>
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Designtime/Ancestor.h>
#include <Core/Parameter.h>
#include <Core/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;

namespace Designtime {

bool checkSyntax(TokenIterator foundIt, const TokenList &expected);

class Parser
{
public:
	static std::string buildConstraintTypename(const std::string& name, const PrototypeConstraints& constraints);

	static TokenList collectScopeTokens(TokenIterator& token);
	static Ancestors collectInheritance(TokenIterator& token);
	static PrototypeConstraints collectPrototypeConstraints(TokenIterator& token);

	static std::string identify(TokenIterator& token);

	static ImplementationType::E parseImplementationType(TokenIterator& token, ImplementationType::E defaultValue);
	static LanguageFeatureState::E parseLanguageFeatureState(TokenIterator& token, LanguageFeatureState::E defaultValue);
	static ObjectType::E parseObjectType(TokenIterator& token);
	static Runtime::AtomicValue parseValueInitialization(TokenIterator& token);

	static bool isEnumDeclaration(TokenIterator start);
	static bool isInterfaceDeclaration(TokenIterator start);
	static bool isLibraryReference(TokenIterator start);
	static bool isLocalDeclaration(TokenIterator start);
	static bool isMemberDeclaration(TokenIterator token);
	static bool isMethodDeclaration(TokenIterator token);
	static bool isNamespaceDeclaration(TokenIterator start);
	static bool isObjectDeclaration(TokenIterator start);
	static bool isParameterDeclaration(TokenIterator start);

	static ParameterList parseParameters(TokenIterator &token, IScope* scope = 0);
};


}
}


#endif
