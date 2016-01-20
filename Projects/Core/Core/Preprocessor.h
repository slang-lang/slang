
#ifndef ObjectiveScript_Preprocessor_h
#define ObjectiveScript_Preprocessor_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Method.h"
#include "Parameter.h"
#include "Tokenizer.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IScope;
class Object;
class Repository;

class Preprocessor
{
public:
	Preprocessor(Repository *repo);

public:
	void process(Object *object);

private:
	Object* createMember(TokenIterator start);
	Method* createMethod(TokenIterator start);

	void generateObject();
	void generateTokens(const std::string& content);

	bool isLocalDeclaration(TokenIterator start);
	bool isMemberDeclaration(TokenIterator start);
	bool isMethodDeclaration(TokenIterator start);
	bool isParameterDeclaration(TokenIterator start);

	ParameterList parseParameters(TokenIterator &token);

private:
	std::string mFilename;
	Object *mObject;
	Repository *mRepository;
	IScope *mScope;
	TokenList mTokens;
};


}


#endif
