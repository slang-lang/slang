
#ifndef ObjectiveScript_Core_AST_TreeGenerator_h
#define ObjectiveScript_Core_AST_TreeGenerator_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Parameter.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include <Core/Scope.h>
#include <Core/VirtualMachine/Stack.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Repository;

namespace Runtime {
	class Namespace;
	class Object;
}

namespace AST {

// Forward declarations
class Node;

class TreeGenerator
{
public:
	TreeGenerator();
	~TreeGenerator();

public:
	AST::Node* generate(const TokenList &tokens);

private: // Execution
	inline Symbol* identify(TokenIterator& token) const;
	inline Symbol* identifyMethod(TokenIterator& token, const ParameterList& params) const;

	// token processing
	// {
	void process(Runtime::Object* result, TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_break(TokenIterator& token);
	void process_continue(TokenIterator& token);
	void process_copy(TokenIterator& token, Runtime::Object* result);
	void process_delete(TokenIterator& token);
	void process_exit(TokenIterator& token);
	void process_for(TokenIterator& token, Runtime::Object* result);
	void process_foreach(TokenIterator& token, Runtime::Object* result);
	void process_identifier(TokenIterator& token, Runtime::Object* result, Token::Type::E terminator = Token::Type::SEMICOLON);
	void process_if(TokenIterator& token, Runtime::Object* result);
	void process_keyword(TokenIterator& token, Runtime::Object* result);
	void process_method(TokenIterator& token, Runtime::Object* result);
	void process_new(TokenIterator& token, Runtime::Object* result);
	void process_print(TokenIterator& token);
	void process_return(TokenIterator& token, Runtime::Object* result);
	void process_scope(TokenIterator& token, Runtime::Object* result);
	void process_switch(TokenIterator& token, Runtime::Object* result);
	void process_throw(TokenIterator& token, Runtime::Object* result);
	void process_try(TokenIterator& token, Runtime::Object* result);
	Runtime::Object* process_type(TokenIterator& token, Symbol* symbol);
	void process_typeid(TokenIterator& token, Runtime::Object* result);
	void process_while(TokenIterator& token, Runtime::Object* result);
	// }

	// expression parsing
	// {
	void expression(Runtime::Object* result, TokenIterator& start);
	void parseCondition(Runtime::Object* result, TokenIterator& start);
	void parseExpression(Runtime::Object* result, TokenIterator& start);
	void parseFactors(Runtime::Object* result, TokenIterator& start);
	void parseInfixPostfix(Runtime::Object* result, TokenIterator& start);
	void parseTerm(Runtime::Object* result, TokenIterator& start);
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

	NamedScope* getEnclosingMethodScope(IScope* scope) const;
	Runtime::Namespace* getEnclosingNamespace(IScope* scope) const;
	Runtime::Object* getEnclosingObject(IScope* scope) const;

private:
	IScope* mOwner;
	Repository *mRepository;
};


}
}


#endif
