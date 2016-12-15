
#ifndef ObjectiveScript_Core_AST_TreeInterpreter_h
#define ObjectiveScript_Core_AST_TreeInterpreter_h


// Library includes

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include <Core/VirtualMachine/Stack.h>
#include <Core/Parameter.h>
#include <Core/Scope.h>
#include "ControlStatements.h"
#include "Expression.h"
#include "Keywords.h"
#include "Operator.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Repository;
namespace Runtime {
	class Method;
	class Namespace;
	class Object;
}

namespace AST {

// Forward declarations
class Statement;
class Statements;

class TreeInterpreter
{
public:
	TreeInterpreter();
	~TreeInterpreter();

public: // Execution
	Runtime::ControlFlow::E execute(Runtime::Method* method, const ParameterList& params, Runtime::Object* result);

private:
	void process(Statements* statements);

	void visit(Node* node);

	void visitExpression(Expression *expression);
	void visitOperator(Operator* op);
	void visitStatement(Statement *node);

	void visitAssert(AssertStatement* node);
	void visitAssignment(Assignment* node);
	void visitBreak(BreakStatement* node);
	void visitContinue(ContinueStatement* node);
	void visitDelete(DeleteStatement* node);
	void visitExit(ExitStatement* node);
	void visitFor(ForStatement* node);
	void visitForeach(ForeachStatement *node);
	void visitIf(IfStatement* node);
	void visitPrint(PrintStatement* node);
	void visitReturn(ReturnStatement* node);
	void visitStatements(Statements* node);
	void visitThrow(ThrowStatement* node);
	void visitTry(TryStatement* node);
	void visitTypeDeclaration(TypeDeclaration* node);
	void visitWhile(WhileStatement* node);

private:
	NamedScope* getEnclosingMethodScope(IScope* scope) const;
	Runtime::Namespace* getEnclosingNamespace(IScope* scope) const;
	Runtime::Object* getEnclosingObject(IScope* scope) const;

	inline Symbol* identify(TokenIterator& token) const;
	inline Symbol* identifyMethod(TokenIterator& token, const ParameterList& params) const;

	// Scope stack
	// {
	IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope = 0);
	// }

	void evaluate(Node* exp, Runtime::Object* result) const;
	void evaluateLiteral(Expression* exp, Runtime::Object* result) const;
	void evaluateVariable(Expression* exp, Runtime::Object* result) const;

	std::string printExpression(Node* node) const;

private:	// Interpreter stuff
	Runtime::ControlFlow::E mControlFlow;
	IScope* mOwner;
	Repository *mRepository;
	Statements* mRootNode;
};


}
}


#endif
