
#ifndef ObjectiveScript_Core_Interpreter_h
#define ObjectiveScript_Core_Interpreter_h


// Library includes
#include <list>

// Project includes
#include <Core/Common/Types.h>
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Method;
	class Namespace;
}
namespace Core {
	class Debugger;
}
class IScope;
class Memory;
class NamedScope;
class Repository;
class Stack;
class Symbol;

namespace Runtime {

// Forward declarations
class Object;


class Interpreter
{
public:
	Interpreter(Common::ThreadId threadId);
	~Interpreter();

public: // Execution
	ControlFlow::E execute(Common::Method* method, const ParameterList& params, Object* result);

private:
	class Initialization {
	public:
		enum E {
			NotAllowed,
			Allowed,
			Required
		};
	};

private: // Execution
	inline void collectParameterList(TokenIterator& token, ParameterList& params, std::list<Object>& objectList);
	inline void collectScopeTokens(TokenIterator& token, TokenList& tokens);

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
	void process_identifier(TokenIterator& token, Object* result);
	void process_if(TokenIterator& token, Object* result);
	void process_keyword(TokenIterator& token, Object* result);
	void process_method(TokenIterator& token, Object* result);
	void process_new(TokenIterator& token, Object* result);
	void process_print(TokenIterator& token);
	void process_return(TokenIterator& token, Object* result);
	void process_scope(TokenIterator& token, Object* result);
	void process_statement(TokenIterator& token, Object* result);
	void process_switch(TokenIterator& token, Object* result);
	void process_throw(TokenIterator& token, Object* result);
	void process_try(TokenIterator& token, Object* result);
	Object* process_type(TokenIterator& token, Symbol* symbol, Initialization::E initialization);
	void process_typeid(TokenIterator& token, Object* result);
	void process_var(TokenIterator& token, Object* result);
	void process_while(TokenIterator& token, Object* result);
	// }

	// expression parsing
	// {
	void expression(Object* result, TokenIterator& start, bool completeEval = true);
	void parseCondition(Object* result, TokenIterator& start);
	void parseExpression(Object* result, TokenIterator& start);
	void parseFactors(Object* result, TokenIterator& start);
	void parseInfixPostfix(Object* result, TokenIterator& start);
	void parseTerm(Object* result, TokenIterator& start);
	// }

	// Parsing helpers
	// {
	AccessMode::E parseAccessMode(TokenIterator &token, bool isAtomicType);
	Mutability::E parseMutability(TokenIterator& token);
	// }

	// Scope stack
	// {
	IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope = 0, bool allowBreakAndContinue = false);
	// }

	// Token stack
	// {
	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

	ControlFlow::E interpret(const TokenList& tokens, Object* result, bool allowBreakAndContinue = false);

	NamedScope* getEnclosingMethodScope(IScope* scope = 0) const;
	Common::Namespace* getEnclosingNamespace(IScope* scope = 0) const;
	Runtime::Object* getEnclosingObject(IScope* scope = 0) const;

private:	// Initialization
	void deinitialize();
	void initialize(IScope* scope, const TokenList& tokens, const ParameterList& params);

private:	// internal stuff
	ControlFlow::E mControlFlow;
	IScope* mOwner;

private:	// Virtual machine stuff
	Core::Debugger* mDebugger;
	Memory* mMemory;
	Repository* mRepository;
	Stack* mStack;
	Common::ThreadId mThreadId;
};


}
}


#endif
