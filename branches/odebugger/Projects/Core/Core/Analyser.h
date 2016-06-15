
#ifndef ObjectiveScript_Analyser_h
#define ObjectiveScript_Analyser_h


// Library includes
#include <string>

// Project includes
#include <Core/Designtime/Ancestor.h>
#include <Core/Designtime/BluePrint.h>
#include <Core/Designtime/Prototype.h>
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class MethodScope;
class Repository;

class Analyser
{
public:
	Analyser(Repository *repository);
	~Analyser();

public:
	const Designtime::BluePrintList& getBluePrints() const;
	const StringList& getLibraryReferences() const;

public:	// Entry points
	void processFile(const std::string& filename);
	void processString(const std::string& content, const std::string& filename = "");
	void processTokens(const TokenList& tokens);

protected:

private:	// moved to private to prevent usage in this release
	const Designtime::PrototypeList& getPrototypes() const;

private:
	void generate(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);
	void process(const TokenList& tokens);

	Designtime::BluePrint createBluePrint(TokenIterator& start, TokenIterator end, bool isInterface = false) const;
	std::string createLibraryReference(TokenIterator& start, TokenIterator end) const;
	void createMember(TokenIterator& start, TokenIterator end);
	void createMethod(TokenIterator& start, TokenIterator end);
	void createNamespace(TokenIterator& start, TokenIterator end);
	Designtime::Prototype createPrototype(TokenIterator& start, TokenIterator end) const;

	Designtime::Ancestors collectInheritance(TokenIterator &start) const;

private:
	Designtime::BluePrintList mBluePrints;
	std::string mFilename;
	StringList mLibraries;
	Designtime::PrototypeList mPrototypes;
	Repository *mRepository;
	MethodScope *mScope;
	std::string mScopeName;
};


}


#endif
