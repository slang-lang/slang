
#ifndef ObjectiveScript_Analyser_h
#define ObjectiveScript_Analyser_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Method.h"
#include "Object.h"
#include "Token.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Analyser
{
public:
	const std::list<std::string>& getLibraryReferences() const;
	const ObjectBluePrintList& getObjects() const;

public:
	void process(const std::string& filename);

protected:

private:
	void generateObjects();
	void generateTokens(const std::string& content);

private:
	std::string createLibraryReference(TokenIterator& start);
	ObjectBluePrint createObject(TokenIterator& start);

private:
	bool isLibraryReference(TokenIterator start);
	bool isObjectDeclaration(TokenIterator start);

private:
	std::string				mFilename;
	std::list<std::string>	mLibraries;
	ObjectBluePrintList		mObjects;
	TokenList				mTokens;
};


}


#endif
