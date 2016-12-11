
#ifndef ObjectiveScript_Core_AST_TreeVisitor_h
#define ObjectiveScript_Core_AST_TreeVisitor_h


// Library includes

// Project includes
#include "ControlStatements.h"
#include "Expression.h"
#include "Keywords.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {

// Forward declarations
class Statement;
class Statements;

class TreeVisitor
{
public:
	TreeVisitor(Statements* root);
	virtual ~TreeVisitor();

public:
	Statements* mRootNode;
};


class PrintVisitor : public TreeVisitor
{
public:
	PrintVisitor(Statements* root);
	~PrintVisitor();

public:
	void process(Statements* root = 0);

private:
	void visitStatement(Statement* node);

	void visitAssert(AssertStatement* node);
	void visitAssignment(Assignment* node);
	void visitBreak(BreakStatement* node);
	void visitContinue(ContinueStatement* node);
	void visitDelete(DeleteStatement* node);
	void visitExit(ExitStatement* node);
	void visitIf(IfStatement* node);
	void visitPrint(PrintStatement* node);
	void visitReturn(ReturnStatement* node);
	void visitThrow(ThrowStatement* node);
	void visitWhile(WhileStatement* node);

private:
	std::string printExpression(Expression* node) const;
	std::string printIndentation(int indentation) const;

private:
	int mIndentation;
};


}
}


#endif
