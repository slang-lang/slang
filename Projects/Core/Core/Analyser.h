
#ifndef ObjectiveScript_Analyser_h
#define ObjectiveScript_Analyser_h


// Library includes
#include <string>

// Project includes
#include "Method.h"
#include "Object.h"
#include "Prototype.h"
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
	Analyser(IScope *scope);
	~Analyser();

public:
	const BluePrintList& getBluePrints() const;
	const StringList& getLibraryReferences() const;

public:
	void process(const std::string& filename);

protected:

private:	// moved to private to prevent usage in this release
	const InterfaceList& getInterfaces() const;
	const PrototypeList& getPrototypes() const;

private:
	void generate(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);

private:
	BluePrint createBluePrint(TokenIterator& start, TokenIterator end);
	Interface createInterface(TokenIterator& start, TokenIterator end);
	std::string createLibraryReference(TokenIterator& start, TokenIterator end);
	void createNamespace(TokenIterator& start, TokenIterator end);
	Prototype createPrototype(TokenIterator& start, TokenIterator end);

private:
	bool isInterfaceDeclaration(TokenIterator start);
	bool isLibraryReference(TokenIterator start);
	bool isNamespaceDeclaration(TokenIterator start);
	bool isObjectDeclaration(TokenIterator start);
	bool isPrototypeDeclaration(TokenIterator start);

private:
	BluePrintList mBluePrints;
	std::string mFilename;
	InterfaceList mInterfaces;
	StringList mLibraries;
	PrototypeList mPrototypes;
	IScope *mScope;
};


}


#endif
