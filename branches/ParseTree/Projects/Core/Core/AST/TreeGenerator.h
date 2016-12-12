
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
#include "Statement.h"

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
class Expression;
class Node;

class TreeGenerator
{
public:
	TreeGenerator();
	~TreeGenerator();

public:
	Statements* generate(const TokenList &tokens);

private: // Execution
	inline Symbol* identify(TokenIterator& token) const;
	inline Symbol* identifyMethod(TokenIterator& token, const ParameterList& params) const;

	// token processing
	// {
	Statements* process(TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	Statement* process_assert(TokenIterator& token);
	Statement* process_break(TokenIterator& token);
	Statement* process_continue(TokenIterator& token);
	Expression* process_copy(TokenIterator& token);
	Statement* process_delete(TokenIterator& token);
	Statement* process_exit(TokenIterator& token);
	Statement* process_for(TokenIterator& token);
	Statement* process_foreach(TokenIterator& token);
	Node* process_identifier(TokenIterator& token, Token::Type::E terminator = Token::Type::SEMICOLON);
	Statement* process_if(TokenIterator& token);
	Node* process_keyword(TokenIterator& token);
	MethodExpression* process_method(TokenIterator& token);
	Expression* process_new(TokenIterator& token);
	Statement* process_print(TokenIterator& token);
	Statement* process_return(TokenIterator& token);
	Statements* process_scope(TokenIterator& token);
	Node* process_statement(TokenIterator& token, Token::Type::E terminator = Token::Type::SEMICOLON);
	Statement* process_switch(TokenIterator& token);
	Statement* process_throw(TokenIterator& token);
	Statement* process_try(TokenIterator& token);
	TypeDeclaration* process_type(TokenIterator& token);
	Expression* process_typeid(TokenIterator& token);
	Statement* process_while(TokenIterator& token);
	// }

	// expression parsing
	// {
	Node* expression(TokenIterator& start);
	Node* parseCondition(TokenIterator& start);
	Node* parseExpression(TokenIterator& start);
	Node* parseFactors(TokenIterator& start);
	Node* parseInfixPostfix(TokenIterator& start);
	Node* parseTerm(TokenIterator& start);
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
