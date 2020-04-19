
#ifndef Slang_Core_Core_AST_PrintVisitor_h
#define Slang_Core_Core_AST_PrintVisitor_h


// Library includes

// Project includes
#include "TreeVisitor.h"
#include "TreeLineBuffer.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace AST {

// Forward declarations
class Statement;
class Statements;

class PrintVisitor : public TreeVisitor
{
public:
	PrintVisitor();

public:
	void generate(Statements* root, TreeLineBuffer& output);

private:
	void visit(Node* node) override;

	void visitExpression(Expression* expression) override;
	void visitOperator(Operator* op) override;
	void visitStatement(Statement* node) override;

	void visitAssert(AssertStatement* node) override;
	void visitBreak(BreakStatement* node) override;
	void visitContinue(ContinueStatement* node) override;
	void visitDelete(DeleteStatement* node) override;
	void visitExit(ExitStatement* node) override;
	void visitFor(ForStatement* node) override;
	void visitForeach(ForeachStatement *node) override;
	void visitIf(IfStatement* node) override;
	void visitPrint(PrintStatement* node) override;
	void visitReturn(ReturnStatement* node) override;
	void visitStatements(Statements* node) override;
	void visitSwitch(SwitchStatement* node) override;
	void visitThrow(ThrowStatement* node) override;
	void visitTry(TryStatement* node) override;
	void visitTypeDeclaration(TypeDeclaration* node) override;
	void visitTypeInference(TypeInference* node) override;
	void visitWhile(WhileStatement* node) override;

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
