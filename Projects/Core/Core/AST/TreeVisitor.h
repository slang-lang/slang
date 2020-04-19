
#ifndef ObjectiveScript_Core_AST_TreeVisitor_h
#define ObjectiveScript_Core_AST_TreeVisitor_h


// Library includes

// Project includes
#include "Expression.h"
#include "Operator.h"
#include "Statement.h"
#include "TreeLineBuffer.h"

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
	TreeVisitor();
	virtual ~TreeVisitor() = default;

protected:
	virtual void visit(Node* node);

	virtual void visitExpression(Expression* expression);
	virtual void visitOperator(Operator* op);
	virtual void visitStatement(Statement* node);

	virtual void visitAssert(AssertStatement* node);
	virtual void visitBreak(BreakStatement* node);
	virtual void visitContinue(ContinueStatement* node);
	virtual void visitDelete(DeleteStatement* node);
	virtual void visitExit(ExitStatement* node);
	virtual void visitFor(ForStatement* node);
	virtual void visitForeach(ForeachStatement *node);
	virtual void visitIf(IfStatement* node);
	virtual void visitPrint(PrintStatement* node);
	virtual void visitReturn(ReturnStatement* node);
	virtual void visitStatements(Statements* node);
	virtual void visitSwitch(SwitchStatement* node);
	virtual void visitThrow(ThrowStatement* node);
	virtual void visitTry(TryStatement* node);
	virtual void visitTypeDeclaration(TypeDeclaration* node);
	virtual void visitTypeInference(TypeInference* node);
	virtual void visitWhile(WhileStatement* node);
};


}
}


#endif
