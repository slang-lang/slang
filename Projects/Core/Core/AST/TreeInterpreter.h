
#ifndef Slang_Core_Core_AST_TreeInterpreter_h
#define Slang_Core_Core_AST_TreeInterpreter_h


// Library includes

// Project includes
#include <Core/Common/Types.h>
#include <Core/Parameter.h>
#include <Core/Runtime/ControlFlow.h>
#include "Expression.h"
#include "Operator.h"
#include "Statement.h"

// Forward declarations

// Namespace declarations


namespace Slang {

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
namespace Runtime {
	class Object;
}
class Repository;
class StackFrame;
class Thread;

namespace AST {

// Forward declarations
class Statement;
class Statements;

class TreeInterpreter
{
public:
	explicit TreeInterpreter(Common::ThreadId id);
	~TreeInterpreter() = default;

public: // Execution
	Runtime::ControlFlow::E execute(Runtime::Object* self, Common::Method* method, const ParameterList& params, Runtime::Object* result);

private:
	void process(Statements* statements);

	inline void visit(Node* node);

	inline void visitExpression(Expression* expression);
	inline void visitOperator(Operator* op);
	inline void visitStatement(Statement* node);

	void visitAssert(AssertStatement* node);
	void visitAssignment(AssignmentStatement* node);
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
	Runtime::Object* visitTypeDeclaration(TypeDeclaration* node);
	Runtime::Object* visitTypeInference(TypeInference* node);
	void visitWhile(WhileStatement* node);

private:
	MethodScope* getEnclosingMethodScope(IScope *scope = nullptr) const;
	NamedScope* getEnclosingNamedScope(IScope *scope = nullptr) const;
	Runtime::Object* getEnclosingObject(IScope* scope = nullptr) const;

	// Scope stack
	// {
	inline IScope* getScope() const;
	inline void popScope();
	inline void pushScope(IScope* scope = nullptr);
	// }

	void evaluate(Node* exp, Runtime::Object* result);
	void evaluateAssignmentExpression(AssignmentExpression* exp, Runtime::Object* result);
	void evaluateBinaryExpression(BinaryExpression* exp, Runtime::Object* result);
	void evaluateBooleanBinaryExpression(BooleanBinaryExpression* exp, Runtime::Object* result);
	void evaluateCopyExpression(CopyExpression* exp, Runtime::Object* result);
	void evaluateIsExpression(IsExpression* exp, Runtime::Object* result);
	void evaluateLiteral(LiteralExpression* exp, Runtime::Object* result);
	void evaluateMethodExpression(MethodExpression* exp, Runtime::Object* result);
	void evaluateNewExpression(NewExpression* exp, Runtime::Object* result);
	void evaluateScopeExpression(ScopeExpression* exp, Runtime::Object* result);
	void evaluateSymbolExpression(SymbolExpression *exp, Runtime::Object *result, IScope *scope);
	void evaluateTernaryExpression(TernaryExpression* exp, Runtime::Object* result);
	void evaluateTypeCastExpression(TypecastExpression* exp, Runtime::Object* result);
	void evaluateTypeidExpression(TypeidExpression* exp, Runtime::Object* result);
	void evaluateUnaryExpression(UnaryExpression* exp, Runtime::Object* result);

	std::string printExpression(Node* node) const;

	Runtime::Object& resolveLValue(IScope *scope, SymbolExpression *symbol, bool onlyCurrentScope, Visibility::E visibility) const;
	Symbol* resolveRValue(IScope *scope, SymbolExpression *symbol, bool onlyCurrentScope, Visibility::E visibility) const;

	MethodSymbol* resolveMethod(IScope* scope, SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) const;

private:	// Initialization
	void finalize();
	void initialize(IScope* scope, const ParameterList& params);

private:	// Interpreter stuff
	Runtime::ControlFlow::E mControlFlow;

private:	// Virtual machine stuff
	Core::Debugger* mDebugger;
	StackFrame* mFrame;
	Memory* mMemory;
	Repository *mRepository;
	Thread* mThread;
};


}
}


#endif
