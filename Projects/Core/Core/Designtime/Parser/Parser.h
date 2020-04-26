
#ifndef Slang_Designtime_Parser_Parser_h
#define Slang_Designtime_Parser_Parser_h


// Library includes

// Project includes
#include <Core/Attributes/Types.h>
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Common/TypeDeclaration.h>
#include <Core/Designtime/Ancestor.h>
#include <Core/Parameter.h>
#include <Core/Attributes/Types.h>
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class IScope;

namespace Designtime {

bool checkSyntax(TokenIterator foundIt, const TokenList& expected);
PrototypeConstraints mergeConstraints(const PrototypeConstraints& designtime, const PrototypeConstraints& runtime);

class Parser
{
public:
	static std::string buildDesigntimeConstraintTypename(const std::string& name, const PrototypeConstraints& constraints);
	static std::string buildRuntimeConstraintTypename(const std::string& name, const PrototypeConstraints& constraints);

	static TokenList collectScopeTokens(TokenIterator& token);
	static Ancestors collectInheritance(TokenIterator& token);
	static PrototypeConstraints collectDesigntimePrototypeConstraints(TokenIterator& token);
	static PrototypeConstraints collectRuntimePrototypeConstraints(TokenIterator& token);

	static std::string identify(TokenIterator& token);

	static bool isEnumDeclaration(TokenIterator token);
	static bool isInterfaceDeclaration(TokenIterator token);
	static bool isLibraryReference(TokenIterator token);
	static bool isMemberDeclaration(TokenIterator token);
	static bool isMethodDeclaration(TokenIterator token);
	static bool isNamespaceDeclaration(TokenIterator token);
	static bool isObjectDeclaration(TokenIterator token);

	static AccessMode::E parseAccessMode(TokenIterator& token, AccessMode::E defaultValue);
	static BlueprintType::E parseBluePrintType(TokenIterator &token);
	static CheckedExceptions::E parseExceptions(TokenIterator& token, CheckedExceptions::E defaultValue = CheckedExceptions::Nothrow);
	static LanguageFeatureState::E parseLanguageFeatureState(TokenIterator& token, LanguageFeatureState::E defaultValue);
	static MemoryLayout::E parseMemoryLayout(TokenIterator& token, MemoryLayout::E defaultValue = MemoryLayout::Instance);
	static Mutability::E parseMutability(TokenIterator& token, Mutability::E defaultValue = Mutability::Modify);
	static ParameterList parseParameters(TokenIterator &token, IScope* scope = 0);
	static Common::TypeDeclaration parseTypeDeclaration(TokenIterator& token, IScope* scope = 0);
	static Runtime::AtomicValue parseValueInitialization(TokenIterator& token, const std::string& type);
	static Virtuality::E parseVirtuality(TokenIterator& token, Virtuality::E defaultValue = Virtuality::Virtual);
	static Visibility::E parseVisibility(TokenIterator& token, Visibility::E defaultValue = Visibility::Private);
};


}
}


#endif
