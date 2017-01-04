
#ifndef ObjectiveScript_Core_Interpreter_h
#define ObjectiveScript_Core_Interpreter_h


// Library includes
#include <list>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include <Core/VirtualMachine/Stack.h>
#include "Parameter.h"
#include "Scope.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Namespace;
}

// Forward declarations
class Repository;

namespace Runtime {

// Forward declarations
class Object;


class Interpreter
{
public:
	Interpreter();
	virtual ~Interpreter();

public: // Execution
	ControlFlow::E execute(Common::Method* method, const ParameterList& params, Object* result);

private: // Execution
	inline Symbol* identify(TokenIterator& token) const;
	inline Symbol* identifyMethod(TokenIterator& token, const ParameterList& params) const;

	// token processing
	// {
	void process(Object* result, TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_break(TokenIterator& token);
	void process_continue(TokenIterator& token);
	void process_copy(TokenIterator& token, Object* result);
	void process_delete(TokenIterator& token);
	void process_exit(TokenIterator& token);
	void process_for(TokenIterator& token, Object* result);
	void process_foreach(TokenIterator& token, Object* result);
	void process_identifier(TokenIterator& token, Object* result, Token::Type::E terminator = Token::Type::SEMICOLON);
	void process_if(TokenIterator& token, Object* result);
	void process_keyword(TokenIterator& token, Object* result);
	void process_method(TokenIterator& token, Object* result);
	void process_new(TokenIterator& token, Object* result);
	void process_print(TokenIterator& token);
	void process_return(TokenIterator& token, Object* result);
	void process_scope(TokenIterator& token, Object* result);
	void process_switch(TokenIterator& token, Object* result);
	void process_throw(TokenIterator& token, Object* result);
	void process_try(TokenIterator& token, Object* result);
	Object* process_type(TokenIterator& token, Symbol* symbol);
	void process_typeid(TokenIterator& token, Object* result);
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
	IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope = 0);
	// }

	// Token stack
	// {
	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

	ControlFlow::E interpret(const TokenList& tokens, Object* result);

	NamedScope* getEnclosingMethodScope(IScope* scope) const;
	Common::Namespace* getEnclosingNamespace(IScope* scope) const;
	Object* getEnclosingObject(IScope* scope) const;

private:
	ControlFlow::E mControlFlow;
	IScope* mOwner;
	Repository *mRepository;
};


}
}


#endif
