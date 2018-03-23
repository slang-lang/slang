
#ifndef ObjectiveScript_Core_Designtime_Analyser_h
#define ObjectiveScript_Core_Designtime_Analyser_h


// Library includes
#include <string>

// Project includes
#include <Core/Common/TypeDeclaration.h>
#include <Core/Designtime/Parser/Token.h>
#include "Ancestor.h"
#include "BluePrintObject.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class MethodScope;
class Repository;

namespace Designtime {


class Analyser
{
public:
	Analyser();
	~Analyser();

public:
	const StringList& getLibraryReferences() const;

public:	// Entry points
	void processFile(const std::string& filename);
	void processString(const std::string& content, const std::string& filename = "");
	void processTokens(const TokenList& tokens);

private:
	void generate(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);

	bool createBluePrint(TokenIterator& token);
	bool createEnum(TokenIterator& token);
	bool createInterface(TokenIterator& token);
	bool createLibraryReference(TokenIterator& token);
	bool createMemberOrMethod(TokenIterator& token);
	bool createNamespace(TokenIterator& token);

	bool createMethodStub(TokenIterator& token, Visibility::E visibility, LanguageFeatureState::E languageFeature, Common::TypeDeclaration type, const std::string& name);
	bool createMemberStub(TokenIterator& token, Visibility::E visibility, LanguageFeatureState::E languageFeature, Common::TypeDeclaration type, const std::string& name);

	bool buildEnum(Designtime::BluePrintObject* symbol, const TokenList& tokens);

private: // type resolution
	std::string getQualifiedTypename(const std::string& name) const;
	std::string resolveType(const std::string& type, const TokenIterator& token) const;
	Common::TypeDeclaration resolveType(const Common::TypeDeclaration& type, const TokenIterator& token) const;

private: // wrapper methods
	Ancestors collectInheritance(TokenIterator& token);
	ParameterList parseParameters(TokenIterator& token, IScope* scope);
	Common::TypeDeclaration parseTypeDeclaration(TokenIterator& token, IScope* scope);

private:
	std::string mFilename;
	StringList mLibraries;
	bool mProcessingInterface;
	Repository* mRepository;
	MethodScope* mScope;
};


}
}


#endif
