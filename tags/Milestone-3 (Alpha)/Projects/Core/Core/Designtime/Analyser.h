
#ifndef ObjectiveScript_Core_Designtime_Analyser_h
#define ObjectiveScript_Core_Designtime_Analyser_h


// Library includes
#include <string>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Token.h>
#include "Ancestor.h"
#include "BluePrintObject.h"
#include "BluePrintEnum.h"

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

protected:

private:
	void generate(const TokenList& tokens);
	TokenList generateTokens(const std::string& content);
	void process(const TokenList& tokens);

	bool createBluePrint(TokenIterator& token, TokenIterator end);
	bool createEnum(TokenIterator& token, TokenIterator end);
	//bool createFunction(TokenIterator& token, TokenIterator end);
	bool createLibraryReference(TokenIterator& token, TokenIterator end);
	bool createMember(TokenIterator& token, TokenIterator end);
	bool createMethod(TokenIterator& token, TokenIterator end);
	bool createNamespace(TokenIterator& token, TokenIterator end);
	//bool createNamespaceMember(TokenIterator& token, TokenIterator end);

	bool buildEnum(Designtime::BluePrintEnum* symbol, const TokenList& tokens);
	std::string getQualifiedTypename(const std::string& name) const;

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