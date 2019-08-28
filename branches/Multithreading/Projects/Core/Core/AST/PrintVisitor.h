
#ifndef ObjectiveScript_Core_AST_PrintVisitor_h
#define ObjectiveScript_Core_AST_PrintVisitor_h


// Library includes

// Project includes
#include "TreeVisitor.h"
#include "TreeLineBuffer.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {

// Forward declarations
class Statement;
class Statements;

class PrintVisitor : public TreeVisitor
{
public:
	PrintVisitor();
	~PrintVisitor();

public:
	void generate(Statements* root, TreeLineBuffer& output);

private:
	void visit(Node* node);

	void visitExpression(Expression* expression);
	void visitOperator(Operator* op);
	void visitStatement(Statement* node);

	void visitAssert(AssertStatement* node);
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
	TreeLineBuffer mOutput;
};


}
}


#endif
