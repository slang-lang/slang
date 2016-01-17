
#ifndef ObjectiveScript_Interpreter_h
#define ObjectiveScript_Interpreter_h


// Library includes
#include <list>

// Project includes
#include "Scope.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Memory;
class Object;
class Repository;

class ControlFlow
{
public:
	typedef enum {
		Break,
		Continue,
		Normal,
		Return,
		Throw
	} E;
};

class Interpreter : public LocalScope,
					public GenericAttributes
{
public:
	Interpreter(IScope *scope, const std::string& name);
	~Interpreter();

public:
	void setRepository(Repository *repository);
	void setTokens(const TokenList& tokens);

public: // Deinit
	void garbageCollector();

public: // Execution
	ControlFlow::E execute(Object *result);

private: // Execution
	Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const;

	// token processing
	// {
	void process(Object *result, TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_break(TokenIterator& token);
	void process_continue(TokenIterator& token);
	void process_delete(TokenIterator& token);
	void process_for(TokenIterator& token);
	void process_identifier(TokenIterator& token, Token::Type::E terminator = Token::Type::SEMICOLON);
	void process_if(TokenIterator& token);
	void process_keyword(TokenIterator& token, Object *result);
	void process_method(TokenIterator& token, Object *result);
	void process_new(TokenIterator& token, Object *result);
	void process_print(TokenIterator& token);
	void process_return(TokenIterator& token, Object *result);
	void process_scope(TokenIterator& token, Object *result);
	void process_throw(TokenIterator& token);
	void process_try(TokenIterator& token);
	void process_type(TokenIterator& token);
	void process_switch(TokenIterator& token);
	void process_while(TokenIterator& token);
	// }

	// expression parsing
	// {
	void expression(Object *result, TokenIterator& start);
	void parseCondition(Object *result, TokenIterator& start);
	void parseExpression(Object *result, TokenIterator& start);
	void parseFactors(Object *result, TokenIterator& start);
	void parseTerm(Object *result, TokenIterator& start);
	// }

	// Token stack
	// {
	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

private:
	typedef std::list<TokenList> TokenStack;

private:
	ControlFlow::E mControlFlow;
	Repository *mRepository;
	TokenList mTokens;
	TokenStack mTokenStack;
};


}


#endif
