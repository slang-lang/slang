
#ifndef ObjectiveScript_Core_AST_TreeGenerator_h
#define ObjectiveScript_Core_AST_TreeGenerator_h


// Library includes
#include <set>

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
namespace Designtime {
	class BluePrintObject;
}
class MethodScope;
namespace Runtime {
	class Object;
}
class Repository;
namespace Runtime {
	class Object;
}
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
	Statements* generateAST(Common::Method* method);

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
	void collectScopeTokens(TokenIterator& token, TokenList& tokens);

	Statements* generate(const TokenList &tokens, bool allowBreakAndContinue = false, bool needsControlStatement = false);

	// token processing
	// {
	Statements* process(TokenIterator& start, TokenIterator end);
	Statement* process_assert(TokenIterator& token);
	Expression* process_assignment(TokenIterator& token, SymbolExpression* lhs);
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
	Expression* process_incdecrement(TokenIterator& token, Expression* lhs);
	Statement* process_keyword(TokenIterator& token);
	MethodExpression* process_method(SymbolExpression* symbol, TokenIterator& token);
	MethodExpression* process_method(SymbolExpression* symbol, const Token& token, const ExpressionList& expressions);
	Expression* process_new(TokenIterator& token);
	Statement* process_print(TokenIterator& token);
	Statement* process_return(TokenIterator& token);
	Statements* process_scope(TokenIterator& token, bool allowBreakAndContinue = false, bool needsControlStatement = false);
	Expression* process_subscript(TokenIterator& token, SymbolExpression* symbol);
	Node* process_statement(TokenIterator& token, bool allowBreakAndContinue = false);
	Statement* process_switch(TokenIterator& token);
	Statement* process_throw(TokenIterator& token);
	Statement* process_try(TokenIterator& token);
	TypeDeclaration* process_type(TokenIterator& token, Initialization::E initialization);
	Expression* process_typeid(TokenIterator& token);
	TypeDeclaration* process_var(TokenIterator& token);
	Statement* process_while(TokenIterator& token);
	// }

	// expression parsing
	// {
	Node* expression(TokenIterator& start);
	Node* parseCondition(TokenIterator& start);
	Node* parseExpression(TokenIterator& start);
	Node* parseFactor(TokenIterator &start);
	Node* parseInfixPostfix(TokenIterator& start);
	Node* parseTerm(TokenIterator& start);
	// }

	// operator processing
	// {
	Node* processIsOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixIncDecOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixNotOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixScopeOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixSubscriptOperator(TokenIterator& start, Node* baseExp);
	Node* processRangeOperator(TokenIterator& start, Node* baseExp);
	Node* processTernaryOperator(TokenIterator& start, Node* baseExp);
	// }

	SymbolExpression* resolve(TokenIterator& token, IScope* base, bool onlyCurrentScope, Visibility::E visibility) const;
	SymbolExpression* resolveWithExceptions(TokenIterator& token, IScope* base) const;
	SymbolExpression* resolveWithThis(TokenIterator& token, IScope* base) const;
	MethodSymbol* resolveMethod(SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) const;
	std::string resolveType(Node* left, const Token& operation, Node* right) const;
	std::string resolveType(const std::string& left, const Token& operation, const std::string& right) const;

	// Scope stack
	// {
	MethodScope* getEnclosingMethodScope(IScope* scope) const;
	MethodScope* getMethodScope(IScope* scope) const;

	inline IScope* getScope() const;
	inline void popScope();
	inline void pushScope(IScope* scope = 0, bool allowBreakAndContinue = false);
	// }

	// Token stack
	// {
	inline const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

private:	// Initialization
	void deinitialize();
	void initialize(Common::Method* method);

private:
	bool mAllowConstModify;
	Runtime::ControlFlow::E mControlFlow;
	Common::Method* mMethod;
	Designtime::BluePrintObject* mThis;
	std::set<std::string> mThrownExceptions;

private:	// Virtual machine stuff
	Repository* mRepository;
	StackFrame* mStackFrame;
	TypeSystem* mTypeSystem;
};


}
}


#endif
