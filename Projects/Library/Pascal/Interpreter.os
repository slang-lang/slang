
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

    private bool processBooleanBinaryExpression(BooleanBinaryExpression exp) const throws {
        //print("processBooleanBinaryExpression(" + exp.toString() + ")");

        string left = processExpression(exp.mLeft);
        string right = processExpression(exp.mRight);

        //print("BooleanBinaryExpression: " + left + " " + exp.mOperator + " " + right);

        switch ( exp.mOperator ) {
            case "AND": { return (float left) && (float right); }
            case "OR":  { return left || right; }
			case "=":   { return left == right; }
			case "<":   { return (float left) < (float right); }
			case "<=":  { return (float left) <= (float right); }
			case ">":   { return (float left) > (float right); }
			case ">=":  { return (float left) >= (float right); }
			case "<>":  { return left != right; }
        }

        throw new RuntimeException("invalid binary operator '" + exp.mOperator + "'!");
    }

    private bool processConstBooleanExpression(ConstBooleanExpression exp) const {
        //print("processConstBooleanExpression(" + exp.toString() + ")");

        return exp.mValue;
    }

    private int processConstIntegerExpression(ConstIntegerExpression exp) const {
        //print("processConstIntegerExpression(" + exp.toString() + ")");

        return exp.mValue;
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
            case ExpressionType.BooleanBinaryExpression: {
                return string processBooleanBinaryExpression(BooleanBinaryExpression exp);
            }
            case ExpressionType.ConstBooleanExpression: {
                return string processConstBooleanExpression(ConstBooleanExpression exp);
            }
            case ExpressionType.ConstIntegerExpression: {
                return string processConstIntegerExpression(ConstIntegerExpression exp);
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

    private void visit(Node node) modify throws {
        if ( !node ) {
            return;
        }

        switch ( node.mNodeType ) {
            case NodeType.ExpressionNode: {
                processExpression(Expression node);
                break;
            }
            case NodeType.OperatorNode: {
                throw new RuntimeException("cannot process operator nodes");
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

    private void visitIfStatement(IfStatement stmt) modify {
        //print("visitIfStatement()");

        var condition = processExpression(stmt.mCondition);
        //print("condition = '" + condition + "'");

        if ( condition == "1" ) {
            visitStatement(stmt.mIfBlock);
        }
        else if ( stmt.mElseBlock ) {
            visitStatement(stmt.mElseBlock);
        }
    }

    private void visitPrintStatement(PrintStatement stmt) const {
        //print("visitPrintStatement()");

        //visitExpression( stmt.mExpression );

        print( processExpression(stmt.mExpression) );
    }

    private void visitStatement(Statement stmt) modify throws {
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
            case StatementType.IfStatement: {
                visitIfStatement(IfStatement stmt);
                break;
            }
            case StatementType.PrintStatement: {
                visitPrintStatement(PrintStatement stmt);
                break;
            }
            case StatementType.ProgramStatement: {
                throw new RuntimeException("statement not allowed here: " + typeid(stmt));
            }
            case StatementType.UnitStatement: {
                throw new RuntimeException("statement not allowed here: " + typeid(stmt));
            }
        }
    }

	protected Map<string, String> mVariables;

    private Statement mProgram;
}
