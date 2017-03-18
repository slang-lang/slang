
#ifndef ObjectiveScript_Core_AST_TreeGenerator_h
#define ObjectiveScript_Core_AST_TreeGenerator_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Parameter.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include <Core/Scope.h>
#include "Statement.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Namespace;
}
class MethodScope;
namespace Runtime {
	class Object;
}
class Repository;
class StackFrame;
class TypeSystem;

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
	Statements* generateAST(Common::Method *method);

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
	inline void collectScopeTokens(TokenIterator& token, TokenList& tokens);

	Statements* generate(const TokenList &tokens, bool allowBreakAndContinue = false);

	Symbol* identify(TokenIterator& token) const;

	// token processing
	// {
	Statements* process(TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	Statement* process_assert(TokenIterator& token);
	Statement* process_break(TokenIterator& token);
	Statement* process_continue(TokenIterator& token);
	Expression* process_copy(TokenIterator& token);
	Statement* process_delete(TokenIterator& token);
	Statement* process_exit(TokenIterator& token);
	Expression* process_expression_keyword(TokenIterator& token);
	Statement* process_for(TokenIterator& token);
	Statement* process_foreach(TokenIterator& token);
	Node* process_identifier(TokenIterator& token, bool allowTypeCast = false);
	Statement* process_if(TokenIterator& token);
	Node* process_keyword(TokenIterator& token);
	MethodExpression* process_method(SymbolExpression* symbol, TokenIterator& token);
	Expression* process_new(TokenIterator& token);
	Statement* process_print(TokenIterator& token);
	Statement* process_return(TokenIterator& token);
	Statements* process_scope(TokenIterator& token, bool allowBreakAndContinue = false);
	Node* process_statement(TokenIterator& token, bool allowBreakAndContinue = false);
	Statement* process_switch(TokenIterator& token);
	Statement* process_throw(TokenIterator& token);
	Statement* process_try(TokenIterator& token);
	TypeDeclaration* process_type(TokenIterator& token, Initialization::E initialization);
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

	SymbolExpression* parseSymbol(TokenIterator& token);
	// }

	// Parsing helpers
	// {
	AccessMode::E parseAccessMode(TokenIterator &token, bool isAtomicType);
	Mutability::E parseMutability(TokenIterator& token);
	// }

	SymbolExpression* resolve(TokenIterator& token, IScope* base) const;
	MethodSymbol* resolveMethod(SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) const;
	std::string resolveType(Node* left, const Token& operation, Node* right) const;

	// Scope stack
	// {
	MethodScope* getEnclosingMethodScope(IScope* scope) const;
	MethodScope* getMethodScope(IScope* scope) const;

	inline IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope = 0, bool allowBreakAndContinue = false);
	// }

	// Token stack
	// {
	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

private:	// Initialization
	void deinitialize();
	void initialize(Common::Method* method);

private:
	bool mHasReturnStatement;
	Common::Method* mMethod;

private:	// Virtual machine stuff
	Repository* mRepository;
	StackFrame* mStackFrame;
	TypeSystem* mTypeSystem;
};


}
}


#endif
