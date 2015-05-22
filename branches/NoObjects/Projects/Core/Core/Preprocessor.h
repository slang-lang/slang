
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
class Object;
class Repository;

class Preprocessor
{
public:
	Preprocessor(Repository *repository);

public:
	void process(Object *object);

protected:

private:
	Object* createMemberObject(const std::string& filename, TokenIterator start);
	Method* createMethod(TokenIterator start);

	void generateObject();
	void generateTokens(const std::string& content);

	bool isLocalDeclaration(TokenIterator start);
	bool isMemberDeclaration(TokenIterator start);
	bool isMethodDeclaration(TokenIterator start);

	ParameterList parseParameters(TokenIterator &token);

private:
	Object *mObject;
	Repository *mRepository;
	TokenList mTokens;
};


}


#endif
