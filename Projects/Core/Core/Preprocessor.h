
#ifndef ObjectiveScript_Preprocessor_h
#define ObjectiveScript_Preprocessor_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Method.h"
#include "Tokenizer.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Object;

class Preprocessor
{
public:
	void process(Object *object);

protected:

private:
	Object createMemberObject(const std::string& filename, TokenIterator start);
	Method createMethod(TokenIterator start);

	void generateObject(Object *object);
	void generateTokens(const std::string& content);

	bool isLocalDeclaration(TokenIterator start);
	bool isMemberDeclaration(TokenIterator start);
	bool isMethodDeclaration(TokenIterator start);
	bool isObjectDeclaration(TokenIterator start);

private:
	TokenList	mTokens;
};


}


#endif
