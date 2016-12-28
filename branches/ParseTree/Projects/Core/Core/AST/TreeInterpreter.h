
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

	void visitExpression(Expression* expression);
	void visitOperator(Operator* op);
	void visitStatement(Statement* node);

	void visitAssert(AssertStatement* node);
	void visitAssignment(Assignment* node);
	void visitBreak(BreakStatement* node);
	void visitContinue(ContinueStatement* node);
	void visitDelete(DeleteStatement* node);
	void visitExit(ExitStatement* node);
	void visitFor(ForStatement* node);
	void visitForeach(ForeachStatement* node);
	void visitIf(IfStatement* node);
	void visitPrint(PrintStatement* node);
	void visitReturn(ReturnStatement* node);
	void visitStatements(Statements* node);
	void visitSwitch(SwitchStatement* node);
	void visitThrow(ThrowStatement* node);
	void visitTry(TryStatement* node);
	void visitTypeDeclaration(TypeDeclaration* node);
	void visitWhile(WhileStatement* node);

private:
	MethodScope* getEnclosingMethodScope(IScope *scope = 0) const;
	NamedScope* getEnclosingNamedScope(IScope *scope = 0) const;
	Runtime::Namespace* getEnclosingNamespace(IScope* scope = 0) const;
	Runtime::Object* getEnclosingObject(IScope* scope = 0) const;

	inline Symbol* identify(TokenIterator& token) const;
	inline Symbol* identifyMethod(TokenIterator& token, const ParameterList& params) const;

	// Scope stack
	// {
	inline IScope* getScope() const;
	void popScope();
	void pushScope(IScope* scope = 0);
	// }

	void evaluate(Node* exp, Runtime::Object* result);
	void evaluateBinaryExpression(BinaryExpression* exp, Runtime::Object* result);
	void evaluateBooleanBinaryExpression(BinaryExpression* exp, Runtime::Object* result);
	void evaluateCopyExpression(CopyExpression* exp, Runtime::Object* result);
	void evaluateLiteral(LiteralExpression* exp, Runtime::Object* result);
	void evaluateMethodExpression(MethodExpression* exp, Runtime::Object* result);
	void evaluateNewExpression(NewExpression* exp, Runtime::Object* result);
	void evaluateUnaryExpression(UnaryExpression* exp, Runtime::Object* result);
	void evaluateVariable(VariableExpression* exp, Runtime::Object* result);

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
