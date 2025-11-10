
#ifndef Slang_Core_Core_AST_TreeGenerator_h
#define Slang_Core_Core_AST_TreeGenerator_h


// Library includes
#include <set>

// Project includes
#include <Core/Common/Namespace.h>
#include <Core/Common/Token.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/Parameter.h>
#include <Core/Scope.h>
#include "Statement.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Common {
	class Method;
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
class StackFrame;
class TypeSystem;

namespace AST {

// Forward declarations
class Expression;
class Node;

class TreeGenerator
{
public:
	explicit TreeGenerator(Repository* repository, bool collectErrors = false);
	~TreeGenerator() = default;

public:
	size_t hasErrors() const;
	void process(MethodScope* base);

private:
	class Initialization {
	public:
		enum E {
			NotAllowed,
			Allowed,
			Required
		};
	};

private: // Generator
	void processBluePrint(Designtime::BluePrintObject* object);
	void processMethod(Common::Method* method);
	void processNamespace(Common::Namespace* space);

	Statements* generateAST(Common::Method* method);

private: // Execution
	void collectScopeTokens(TokenIterator& token, TokenList& tokens);

	Statements* generate(const TokenList& tokens, bool allowBreakAndContinue = false, bool needsControlStatement = false);

	// token processing
	// {
	Statements* process(TokenIterator& start, TokenIterator end);
	Statement* process_assert(TokenIterator& token);
	Node* process_assignment(TokenIterator& token);
	Expression* process_assignment_expression(TokenIterator& token, SymbolExpression* lhs);
	Statement* process_break(TokenIterator& token);
	Expression* process_cast(TokenIterator& token);
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
	Node* process_statement(TokenIterator& token, bool allowBreakAndContinue = false);
	Expression* process_streval(TokenIterator& token);
	Expression* process_subscript(TokenIterator& token, SymbolExpression* symbol);
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
	Node* parseInfix(TokenIterator &start);
	Node* parsePostfix(TokenIterator& start, Node* baseExp);
	Node* parseTerm(TokenIterator& start);
	// }

	// operator processing
	// {
	Node* processIsOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixIncDecOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixNotOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixObjectOperator(const std::string& objectType, TokenIterator& start, Expression* baseExp);
	Node* processPostfixRangeOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixScopeOperator(TokenIterator& start, Node* baseExp);
	Node* processPostfixSubscriptOperator(TokenIterator& start, Node* baseExp);
	Node* processTernaryOperator(TokenIterator& start, Node* baseExp);
	// }

	SymbolExpression* resolve(TokenIterator& token, IScope* base, bool onlyCurrentScope, Visibility::E visibility) const;
	SymbolExpression* resolveLocal(TokenIterator& token) const;
	SymbolExpression* resolveWithExceptions(TokenIterator& token, IScope* base) const;
	SymbolExpression* resolveWithThis(TokenIterator& token, IScope* base) const;
	static MethodSymbol* resolveMethod(SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) ;
	std::string resolveType(TokenIterator& token, Node* left, const Token& operation, Node* right) const;
	std::string resolveType(TokenIterator& token, const std::string& left, const Token& operation, const std::string& right) const;

	// Scope stack
	// {
	static MethodScope* getEnclosingMethodScope(IScope* scope) ;
	static MethodScope* getMethodScope(IScope* scope) ;

	inline IScope* getScope() const;
	inline void popScope();
	inline void pushScope(IScope* scope = nullptr, bool allowBreakAndContinue = false);
	// }

	// Token stack
	// {
	inline const TokenList& getTokens() const;
	inline void popTokens();
	inline void pushTokens(const TokenList& tokens);
	// }

	// Helpers
	// {
	static std::list<MethodSymbol*> provideSimilarMethods(SymbolExpression* symbol) ;
	// }

private:	// Initialization
	void finalize();
	void initialize(Common::Method* method);

private: // Generator
	bool mCollectErrors;
	size_t mErrorCount;

private:
	bool mAllowConstModify;
	Runtime::ControlFlow::E mControlFlow;
	Common::Method* mMethod;
	Designtime::BluePrintObject* mThis;
	std::set<std::string> mThrownExceptions;

private:	// Virtual machine stuff
	Repository* mRepository;
	StackFrame* mStackFrame;
};


}
}


#endif
