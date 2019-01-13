
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
		mConstants = new Map<string, String>();
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
			case "DIV": {
				return "" + int "" + ((int left) / (int right));
			}
			case "+": {
				if ( exp.mLeft.mResultType == "STRING" ) {
					return left + right;
				}
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

    private string processConstantExpression(ConstantExpression exp) const throws {
        //print("processConstantExpression(" + exp.toString() + ")");

        String obj;
        string name = (ConstantExpression exp).mConstant;

        if ( !mConstants.contains(name) ) {
            throw new RuntimeException("Constant '" + name + "' is unknown");
        }
        else {
            obj = mConstants.get(name);
        }

        return string obj;
    }

    private bool processLiteralBooleanExpression(LiteralBooleanExpression exp) const {
        //print("processLiteralBooleanExpression(" + exp.toString() + ")");

        return exp.mValue;
    }

    private int processLiteralIntegerExpression(LiteralIntegerExpression exp) const {
        //print("processLiteralIntegerExpression(" + exp.toString() + ")");

        return exp.mValue;
    }

    private float processLiteralRealExpression(LiteralRealExpression exp) const {
        //print("processLiteralRealExpression(" + exp.toString() + ")");

        return exp.mValue;
    }

    private string processLiteralStringExpression(LiteralStringExpression exp) const {
        //print("processLiteralStringExpression(" + exp.toString() + ")");

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
            case ExpressionType.ConstantExpression: {
	        return string processConstantExpression(ConstantExpression exp);
            }
            case ExpressionType.LiteralBooleanExpression: {
                return string processLiteralBooleanExpression(LiteralBooleanExpression exp);
            }
            case ExpressionType.LiteralIntegerExpression: {
                return string processLiteralIntegerExpression(LiteralIntegerExpression exp);
            }
            case ExpressionType.LiteralRealExpression: {
                return string processLiteralRealExpression(LiteralRealExpression exp);
            }
            case ExpressionType.LiteralStringExpression: {
                return processLiteralStringExpression(LiteralStringExpression exp);
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

    private void visitAssignStatement(AssignmentStatement assign) modify throws {
        //print("visitAssignStatement()");

        String obj;
        string varName = (VariableExpression assign.mLeft).mVariable;

        if ( !mVariables.contains(varName) ) {
            throw new RuntimeException("unknown variable '" + varName + "' referenced");
        }
        else {
            obj = mVariables.get(varName);
        }

        obj = processExpression(assign.mRight);
    }

    private void visitCompoundStatement(CompoundStatement compound) modify {
        //print("visitCompoundStatement()");

        if ( compound.mConstantDeclarations ) {
            visitConstantDeclarationStatement(compound.mConstantDeclarations);
        }

        if ( compound.mVariableDeclarations ) {
            visitVariableDeclarationStatement(compound.mVariableDeclarations);
        }

        foreach ( Statement stmt : compound.mStatements ) {
            visitStatement(stmt);
        }
    }

    protected void visitConstantDeclarationStatement(ConstantDeclarationStatement stmt) modify throws {
        //print("visitConstantDeclarationStatement()");

        foreach ( DeclarationStatement declStmt : stmt.mDeclarations ) {
            string name = declStmt.mName;
            if ( mConstants.contains( name ) ) {
                throw new RuntimeException("duplicate constant '" + name + "' declared");
            }

            var obj = new String("0");
            mConstants.insert(name, obj);

            if ( declStmt.mValue ) {
                obj = processExpression(declStmt.mValue);
            }
        }
    }

    private void visitIfStatement(IfStatement stmt) modify {
        //print("visitIfStatement()");

        var condition = processExpression(stmt.mCondition);

        if ( condition == "1" ) {
            visitStatement(stmt.mIfBlock);
        }
        else if ( stmt.mElseBlock ) {
            visitStatement(stmt.mElseBlock);
        }
    }

    private void visitPrintStatement(PrintStatement stmt) const {
        //print("visitPrintStatement()");

        print( processExpression(stmt.mExpression) );
    }

    protected void visitStatement(Statement stmt) modify throws {
        if ( !stmt ) {
            return;
        }

        switch ( stmt.mStatementType ) {
            case StatementType.AssignmentStatement: {
                visitAssignStatement(AssignmentStatement stmt);
                break;
            }
            case StatementType.CompoundStatement: {
                visitCompoundStatement(CompoundStatement stmt);
                break;
            }
            case StatementType.ConstantDeclarationStatement: {
                throw new RuntimeException("inline constant declarations are not allowed");
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
            case StatementType.VariableDeclarationStatement: {
                throw new RuntimeException("inline variable declarations are not allowed");
            }
            case StatementType.WhileStatement: {
                visitWhileStatement(WhileStatement stmt);
                break;
            }
            default: {
                throw new RuntimeException("unknown statement type(" + (string stmt.mStatementType) + ") detected!");
            }
        }
    }

    protected void visitVariableDeclarationStatement(VariableDeclarationStatement stmt) modify throws {
        //print("visitVariableDeclarationStatement()");

        foreach ( DeclarationStatement declStmt : stmt.mDeclarations ) {
            string name = declStmt.mName;
            if ( mVariables.contains( name ) ) {
                throw new RuntimeException("duplicate constant '" + name + "' declared");
            }

            var obj = new String("0");
            mVariables.insert(name, obj);

            if ( declStmt.mValue ) {
                obj = processExpression(declStmt.mValue);
            }
        }
    }

    private void visitWhileStatement(WhileStatement stmt) modify throws {
	    //print("visitWhileStatement()");

        while ( true ) {
            var condition = processExpression( stmt.mCondition );
            if ( condition != "1" ) {
                break;
            }

            visitStatement( stmt.mBody );
        }
    }

    protected Map<string, String> mConstants;
    protected Statement mProgram;
    protected Map<string, String> mVariables;
}
