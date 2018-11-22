
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

    private string processBinaryExpression(BinaryExpression exp) const throws {
        //print("processBinaryExpression(" + exp.toString() + ")");

        string left = processExpression(exp.mLeft);
        string right = processExpression(exp.mRight);

        //print("BinaryExpression: " + left + " " + exp.mOperator + " " + right);

        switch ( exp.mOperator ) {
			// compare operators
			case "=": {
				return "" + (left == right);
			}
			case "<": {
				return "" + ((float left) < (float right));
			}
			case "<=": {
				return "" + ((float left) <= (float right));
			}
			case ">": {
				return "" + ((float left) > (float right));
			}
			case ">=": {
				return "" + ((float left) >= (float right));
			}
			case "<>": {
				return "" + (left != right);
			}

			// arithmetic operators
			case "+": {
				return "" + ((float left) + (float right));
			}
			case "-": {
				return "" + ((float left) - (float right));
			}
			case "*": {
				return "" + ((float left) * (float right));
			}
			case "/": {
				return "" + ((float left) / (float right));
			}
			case "%": {
				return "" + ((int left) % (int right));
			}
        }

        throw new RuntimeException("invalid binary operator '" + exp.mOperator + "'!");
    }

    private string processConstIntegerExpression(ConstIntegerExpression exp) const {
        //print("processConstIntegerExpression(" + exp.toString() + ")");

        return string exp.mValue;
    }

    private string processConstStringExpression(ConstStringExpression exp) const {
        //print("processConstStringExpression(" + exp.toString() + ")");

        return exp.mValue;
    }

    private string processExpression(Expression exp) const throws {
        //print("processExpression(" + exp.toString() + ")");

        switch ( exp.mExpressionType ) {
            case ExpressionType.BinaryExpression: {
                return processBinaryExpression(BinaryExpression exp);
            }
            case ExpressionType.ConstExpression: {
                throw new RuntimeException("ConstExpressions are not supported by now");
            }
            case ExpressionType.ConstIntegerExpression: {
                return processConstIntegerExpression(ConstIntegerExpression exp);
            }
            case ExpressionType.ConstStringExpression: {
                return processConstStringExpression(ConstStringExpression exp);
            }
            case ExpressionType.UnaryExpression: {
                return processUnaryExpression(UnaryExpression exp);
            }
            case ExpressionType.VariableExpression: {
                return processVariableExpression(VariableExpression exp);
            }
        }
    }

    private string processUnaryExpression(UnaryExpression exp) const throws {
        //print("processUnaryExpression(" + exp.toString() + ")");

        switch ( exp.mOperator ) {
            case "+": {
                return processExpression(exp.mExpression);
            }
            case "-": {
                return "-" + processExpression(exp.mExpression);
            }
        }

        throw new RuntimeException("invalid unary operator '" + exp.mOperator + "'!");
    }

    private string processVariableExpression(VariableExpression exp) const throws {
        //print("processVariableExpression(" + exp.toString() + ")");

        String obj;
        string varName = (VariableExpression exp).mVariable;

        if ( !mVariables.contains(varName) ) {
            throw new RuntimeException("Variable '" + varName + "' is unknown");
        }
        else {
            obj = mVariables.get(varName);
        }

        return string obj;
    }

    private void visit(Node node) modify {
        if ( !node ) {
            return;
        }

        switch ( node.mNodeType ) {
            case NodeType.ExpressionNode: {
                processExpression(Expression node);
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
        //print("visitAssignStatement()");

        String obj;
        string varName = (VariableExpression assign.mLeft).mVariable;

        if ( !mVariables.contains(varName) ) {
            obj = new String("0");
            mVariables.insert(varName, obj);
        }
        else {
            obj = mVariables.get(varName);
        }

        obj = processExpression(assign.mRight);
    }

    private void visitCompoundStatement(CompoundStatement compound) modify {
        //print("visitCompoundStatement()");

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

    private void visitPrintStatement(PrintStatement stmt) const {
        //print("visitPrintStatement()");

        //visitExpression( stmt.mExpression );

        print( processExpression(stmt.mExpression) );
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
