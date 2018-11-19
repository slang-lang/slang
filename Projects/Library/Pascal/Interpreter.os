
// library imports
import System.Collections.Map;
import System.Exception;

// project imports
import Expressions;
import Statements;


public enum ControlFlow {
	Exit,
	Normal;
}


public object RuntimeException const implements IException {
    public void Constructor(string msg) {
        mMessage = msg;
    }

    public string what() const {
        return mMessage;
    }

    private string mMessage const;
}


public object Interpreter {
    public void Constructor(Statement program) {
        mProgram = program;
		mVariables = new Map<string, String>();
    }

    public int run() modify throws {
        if ( !mProgram ) {
            return -1;
        }

        print("Interpreting \"" + (ProgramStatement mProgram).mName + "\"...");

        visitCompoundStatement((ProgramStatement mProgram).mStatements);

        return 0;
    }

    private void visit(Node node) modify {
        if ( !node ) {
            return;
        }

        switch ( node.mNodeType ) {
            case NodeType.ExpressionNode: {
                visitExpression(Expression node);
                break;
            }
            case NodeType.OperatorNode: {
                //visitOperator(Operator node);
                break;
            }
            case NodeType.StatementNode: {
                visitStatement(Statement node);
                break;
            }
        }
    }

    private void visitAssignStatement(AssignmentStatement assign) modify {
        print("visitAssignStatement()");

        visitExpression(assign.mLeft);
        write( " := " );
        visitExpression(assign.mRight);
        writeln(";");
    }

    private void visitCompoundStatement(CompoundStatement compound) modify {
        print("visitCompoundStatement()");

        foreach ( Statement stmt : compound.mStatements ) {
            visitStatement(stmt);
        }
    }

    private void visitExpression(Expression exp) const {
        //print("visitExpression()");

        if ( !exp ) {
            return;
        }

        switch ( exp.mExpressionType ) {
            case ExpressionType.BinaryExpression: {
                visitExpression( (BinaryExpression exp).mLeft );
                write( " " + (BinaryExpression exp).mOperator + " " );
                visitExpression( (BinaryExpression exp).mRight );
                break;
            }
            case ExpressionType.ConstIntegerExpression: {
                int value = (ConstIntegerExpression exp).mValue;
                write( string value );
                break;
            }
            case ExpressionType.ConstStringExpression: {
                write( "'" + (ConstStringExpression exp).mValue + "'" );
                break;
            }
            case ExpressionType.UnaryExpression: {
                write( (UnaryExpression exp).mOperator );
                visitExpression( (UnaryExpression exp).mExpression );
                break;
            }
            case ExpressionType.VariableExpression: {
                write( (VariableExpression exp).mVariable );
                break;
            }
        }
    }

/*
    private void visitOperator(Operator op) modify {
        print("visitOperator()");

        if ( !op ) {
            return;
        }
    }
*/

    private void visitPrintStatement(PrintStatement stmt) const {
        print("visitPrintStatement()");

        visitExpression( stmt.mExpression );
        writeln("");
    }

    private void visitStatement(Statement stmt) modify {
        if ( !stmt ) {
            return;
        }

        switch ( stmt.mStatementType ) {
            case StatementType.CompoundStatement: {
                visitCompoundStatement(CompoundStatement stmt);
                break;
            }
            case StatementType.AssignmentStatement: {
                visitAssignStatement(AssignmentStatement stmt);
                break;
            }
            case StatementType.PrintStatement: {
                visitPrintStatement(PrintStatement stmt);
                break;
            }
        }
    }

	protected Map<string, String> mVariables;

    private Statement mProgram;
}
