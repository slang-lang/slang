
#ifndef ObjectiveScript_Analyser_h
#define ObjectiveScript_Analyser_h


// Library includes
#include <string>

// Project includes
#include <Core/Designtime/Ancestor.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BluePrintEnum.h>
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
	const StringList& getLibraryReferences() const;

public:	// Entry points
	void processFile(const std::string& filename);
	void processString(const std::string& content, const std::string& filename = "");
	void processTokens(const TokenList& tokens);

protected:

private:
	void generate(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);
	void process(const TokenList& tokens);

	bool createBluePrint(TokenIterator& token, TokenIterator end, bool isInterface = false) const;
	bool createEnum(TokenIterator& token, TokenIterator end) const;
	std::string createLibraryReference(TokenIterator& token, TokenIterator end) const;
	bool createMember(TokenIterator& token, TokenIterator end);
	bool createMethod(TokenIterator& token, TokenIterator end);
	bool createNamespace(TokenIterator& token, TokenIterator end);
	bool createPrototype(TokenIterator& token, TokenIterator end) const;

	Designtime::Ancestors collectInheritance(TokenIterator& token) const;
	std::string getQualifiedTypename(const std::string& name) const;
	std::string identify(TokenIterator& start, TokenIterator end) const;

private:
	std::string mFilename;
	StringList mLibraries;
	Repository *mRepository;
	MethodScope *mScope;
	std::string mScopeName;
};


}


#endif
