
#ifndef ObjectiveScript_Interpreter_h
#define ObjectiveScript_Interpreter_h


// Library includes

// Project includes
#include "Object.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Memory;
class Repository;

class Interpreter
{
public:
	Interpreter();
	~Interpreter();

public:	// Setup
	void setMemory(Memory *memory);
	void setScope(const std::string& scope);
	void setRepository(Repository *repository);

public:
	void execute(const TokenList& tokens);

protected:

private:
	void addIdentifier(Object object);			// throws DuplicateIdentifer exception

	TokenIterator consumeToken();

	Object& getSymbol(const std::string& token);

	// condition evaluation
	// {
	Object parseCondition(TokenIterator& start);
	// }

	// expression evaluation
	// {
	Object parseExpression(TokenIterator& start);
	Object parseFactors(TokenIterator& start);
	Object parseTerm(TokenIterator& start);
	// }

	Object process();

	void process_assert(TokenIterator& token);
	Object process_new(TokenIterator& token);
	void process_print(TokenIterator& token);
	void process_type(TokenIterator& token);

private:
	Memory *mMemory;
	Repository *mRepository;
	std::string mScope;
	TokenList mTokens;
};


}


#endif
