
#ifndef ObjectiveScript_Analyser_h
#define ObjectiveScript_Analyser_h


// Library includes
#include <string>

// Project includes
#include <Core/Designtime/Ancestor.h>
#include <Core/Designtime/BluePrint.h>
#include <Core/Designtime/Prototype.h>
#include "Method.h"
#include "Object.h"
#include "Token.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;

class Analyser
{
public:
	Analyser();
	~Analyser();

public:
	const Designtime::BluePrintList& getBluePrints() const;
	const StringList& getLibraryReferences() const;

public:
	void processFile(const std::string& filename);
	void processString(const std::string& content, const std::string& filename = "");

protected:

private:	// moved to private to prevent usage in this release
	const Designtime::PrototypeList& getPrototypes() const;

private:
	void generate(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);
	void process(const std::string& content);

	Designtime::BluePrint createBluePrint(TokenIterator& start, TokenIterator end);
	std::string createLibraryReference(TokenIterator& start, TokenIterator end);
	void createNamespace(TokenIterator& start, TokenIterator end);
	Designtime::Prototype createPrototype(TokenIterator& start, TokenIterator end);

	Designtime::Ancestors collectInheritance(TokenIterator &start) const;
	TokenList collectScopeTokens(TokenIterator& token) const;

	bool isInterfaceDeclaration(TokenIterator start);
	bool isLibraryReference(TokenIterator start);
	bool isNamespaceDeclaration(TokenIterator start);
	bool isObjectDeclaration(TokenIterator start);
	bool isPrototypeDeclaration(TokenIterator start);

private:
	Designtime::BluePrintList mBluePrints;
	std::string mFilename;
	StringList mLibraries;
	Designtime::PrototypeList mPrototypes;
	std::string mScopeName;

	// Comparator token lists
	TokenList mInterfaceDeclaration;
	TokenList mLibraryDeclaration;
	TokenList mNamespaceDeclaration;
	TokenList mObjectDeclaration;
	TokenList mPrototypeDeclaration;
};


}


#endif
