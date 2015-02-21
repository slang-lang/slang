
#ifndef ObjectiveScript_Analyser_h
#define ObjectiveScript_Analyser_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Method.h"
#include "Object.h"
#include "Prototype.h"
#include "Token.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Analyser
{
public:
	const InterfaceList& getInterfaces() const;
	const std::list<std::string>& getLibraryReferences() const;
	const BluePrintList& getObjects() const;
	const PrototypeList& getPrototypes() const;

public:
	void process(const std::string& filename);

protected:

private:
	void generateObjects();
	void generateTokens(const std::string& content);

private:
	Interface createInterface(TokenIterator& start);
	std::string createLibraryReference(TokenIterator& start);
	BluePrint createObject(TokenIterator& start);
	Prototype createPrototype(TokenIterator& start);

private:
	bool isInterfaceDeclaration(TokenIterator start);
	bool isLibraryReference(TokenIterator start);
	bool isObjectDeclaration(TokenIterator start);
	bool isPrototypeDeclaration(TokenIterator start);

private:
	std::string				mFilename;
	InterfaceList			mInterfaces;
	std::list<std::string>	mLibraries;
	BluePrintList			mObjects;
	PrototypeList			mPrototypes;
	TokenList				mTokens;
};


}


#endif
