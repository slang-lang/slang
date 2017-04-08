
#ifndef ObjectiveScript_Core_AST_TreeVisitor_h
#define ObjectiveScript_Core_AST_TreeVisitor_h


// Library includes

// Project includes
#include "ControlStatements.h"
#include "Expression.h"
#include "Keywords.h"
#include "Operator.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {

// Forward declarations
class Statement;
class Statements;

class PrintVisitor
{
public:
	PrintVisitor(Statements* root);
	~PrintVisitor();

public:
	void process(Statements* root = 0);

private:
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
	void visitForeach(ForeachStatement *node);
	void visitIf(IfStatement* node);
	void visitPrint(PrintStatement* node);
	void visitReturn(ReturnStatement* node);
	void visitSwitch(SwitchStatement* node);
	void visitThrow(ThrowStatement* node);
	void visitTry(TryStatement* node);
	void visitTypeDeclaration(TypeDeclaration* node);
	void visitTypeInference(TypeInference* node);
	void visitWhile(WhileStatement* node);

private:
	std::string printExpression(Node* node) const;
	std::string printIndentation(int indentation) const;

private:
	int mIndentation;
	Statements* mRootNode;
};


}
}


#endif
