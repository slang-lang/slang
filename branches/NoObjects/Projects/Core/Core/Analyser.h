
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
	Analyser();
	~Analyser();

public:
	const InterfaceList& getInterfaces() const;
	const StringList& getLibraryReferences() const;
	const BluePrintList& getObjects() const;
	const PrototypeList& getPrototypes() const;

public:
	void process(const std::string& filename);

protected:

private:
	void generateObjects(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);

private:
	Interface createInterface(TokenIterator& start, TokenIterator end);
	std::string createLibraryReference(TokenIterator& start, TokenIterator end);
	void createNamespace(TokenIterator& start, TokenIterator end);
	BluePrint createObject(TokenIterator& start, TokenIterator end);
	Prototype createPrototype(TokenIterator& start, TokenIterator end);

private:
	bool isInterfaceDeclaration(TokenIterator start);
	bool isLibraryReference(TokenIterator start);
	bool isNamespaceDeclaration(TokenIterator start);
	bool isObjectDeclaration(TokenIterator start);
	bool isPrototypeDeclaration(TokenIterator start);

private:
	std::string mFilename;
	InterfaceList mInterfaces;
	StringList mLibraries;
	BluePrintList mObjects;
	PrototypeList mPrototypes;
	IScope *mScope;
};


}


#endif
