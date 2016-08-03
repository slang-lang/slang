
#ifndef ObjectiveScript_Interpreter_h
#define ObjectiveScript_Interpreter_h


// Library includes
#include <list>

// Project includes
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include "Parameter.h"
#include "Scope.h"
#include "Token.h"
#include "Repository.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Repository;

namespace Runtime {

// Forward declarations
class Namespace;
class Object;


class Interpreter
{
public:
	Interpreter(SymbolScope* scope);
	virtual ~Interpreter();

public:
	void setRepository(Repository* repository);
	void setTokens(const TokenList& tokens);

public: // Execution
	ControlFlow::E execute(Object* result);
	const ExceptionData& getExceptionData() const;

private: // private types
	typedef std::list<SymbolScope*> ScopeStack;
	typedef std::list<TokenList> TokenStack;

private: // Deinit
	void garbageCollector();

private: // Execution
	inline Symbol* identify(TokenIterator& token) const;
	Symbol* identifyMethod(TokenIterator& token, const ParameterList& params) const;

	// token processing
	// {
	void process(Object* result, TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_break(TokenIterator& token);
	void process_continue(TokenIterator& token);
	void process_delete(TokenIterator& token);
	void process_exit(TokenIterator& token);
	void process_for(TokenIterator& token, Object* result);
	void process_identifier(TokenIterator& token, Object* result, Token::Type::E terminator = Token::Type::SEMICOLON);
	void process_if(TokenIterator& token, Object* result);
	void process_keyword(TokenIterator& token, Object* result);
	void process_method(TokenIterator& token, Object* result);
	void process_new(TokenIterator& token, Object* result);
	void process_print(TokenIterator& token);
	void process_return(TokenIterator& token, Object* result);
	void process_scope(TokenIterator& token, Object* result);
	void process_throw(TokenIterator& token, Object* result);
	void process_try(TokenIterator& token, Object* result);
	Object* process_type(TokenIterator& token, Symbol* symbol);
	void process_switch(TokenIterator& token, Object* result);
	void process_while(TokenIterator& token, Object* result);
	// }

	// expression parsing
	// {
	void expression(Object* result, TokenIterator& start);
	void parseCondition(Object* result, TokenIterator& start);
	void parseExpression(Object* result, TokenIterator& start);
	void parseFactors(Object* result, TokenIterator& start);
	void parseInfixPostfix(Object* result, TokenIterator& start);
	void parseTerm(Object* result, TokenIterator& start);
	// }

	// Repository
	// {
	Repository* getRepository() const;
	// }

	// Scope stack
	// {
	SymbolScope* getScope() const;
	void pushScope();
	void popScope();
	// }

	// Token stack
	// {
	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

	ControlFlow::E interpret(const TokenList& tokens, Object* result);

	Namespace* getEnclosingSpace() const;

private:
	ControlFlow::E mControlFlow;
	ExceptionData mExceptionData;
	SymbolScope* mOwner;
	Repository *mRepository;
	ScopeStack mScopeStack;
	TokenList mTokens;
	TokenStack mTokenStack;
};


}
}


#endif
