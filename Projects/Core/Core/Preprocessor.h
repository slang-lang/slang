
#ifndef ObjectiveScript_Preprocessor_h
#define ObjectiveScript_Preprocessor_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Designtime/BluePrint.h>
#include "Method.h"
#include "Parameter.h"
#include "Tokenizer.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;
namespace Runtime {
	class Object;
}
class Repository;

class Preprocessor
{
public:
	Preprocessor(Repository *repo);

public:
	void process(Designtime::BluePrint* blueprint);

private:
	Designtime::BluePrint* createMember(TokenIterator start);
	Runtime::Method* createMethod(TokenIterator start);

	TokenList collectScopeTokens(TokenIterator& token) const;

	void generateObject();
	void generateTokens(const std::string& content);

	bool isLocalDeclaration(TokenIterator start);
	bool isMemberDeclaration(TokenIterator start);
	bool isMethodDeclaration(TokenIterator start);
	bool isParameterDeclaration(TokenIterator start);

	ParameterList parseParameters(TokenIterator &token);

private:
	std::string mFilename;
	Designtime::BluePrint *mBluePrint;
	Repository *mRepository;
	IScope *mScope;
	TokenList mTokens;
};


}


#endif
