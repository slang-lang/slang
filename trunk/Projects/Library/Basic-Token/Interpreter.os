
// library imports
import System.Collections.Map;
import System.Collections.Stack;
import System.String;

// project imports
import Line;


public int FIRST_LINE const = 10;

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
	public void Constructor(Object lines) {
		assert(lines is Map<int, Line>);

		mCurrentLine = FIRST_LINE;
		mForStack = new Map<string, int>();
		mLines = Map<int, Line> lines;
		mReturnStack = new Stack<int>();
		mVariables = new Map<string, String>();
	}

	public int run(bool debug = false) modify throws {
		if ( !mLines || mLines.empty() ) {
			throw new Exception("no valid lines to interpret!");
		}

		mForStack.clear();
		mReturnStack.clear();
		mVariables.clear();

		if ( debug ) {
			print("Started interpreting statements...");
		}

		try {
			Line line;

			while ( mCurrentLine > 0 ) {
				//print("LINE: " + mCurrentLine);

				line = mLines.get(mCurrentLine);

				mCurrentLine = process(line.mStatement) ?: line.nextLine();
			}
		}
		catch ( ControlFlow e ) {
			switch ( e ) {
				case ControlFlow.Exit: {
					//print("ControlFlow: Exit");
					break;
				}
				case ControlFlow.Normal: {
					//print("ControlFlow: Normal");
					break;
				}
				default: {
					print("ControlFlow: Unknown!");
					break;
				}
			}
		}

		if ( debug ) {
			print("Done interpreting.");
		}

		return 0;
	}

	protected int process(Statement stmt) modify throws {
		//print("process(" + stmt.toString() + ")");

		switch ( stmt.mStatementType ) {
			case StatementType.DimStatement: {
				return processDIM(DimStatement stmt);
			}
			case StatementType.EndStatement: {
				return processEND(EndStatement stmt);
			}
			case StatementType.ForStatement: {
				return processFOR(ForStatement stmt);
			}
			case StatementType.GoSubStatement: {
				return processGOSUB(GotoStatement stmt);
			}
			case StatementType.GotoStatement: {
				return processGOTO(GotoStatement stmt);
			}
			case StatementType.IfStatement: {
				return processIF(IfStatement stmt);
			}
			case StatementType.InputStatement: {
				return processINPUT(InputStatement stmt);
			}
			case StatementType.LetStatement: {
				return processLET(LetStatement stmt);
			}
			case StatementType.MethodStatement: {
				throw "Method statement is not yet implemented";
			}
			case StatementType.NextStatement: {
				return processNEXT(NextStatement stmt);
			}
			case StatementType.OnStatement: {
				throw "ON is not yet implemented";
			}
			case StatementType.PeekStatement: {
				throw "PEEK is not yet implemented";
			}
			case StatementType.PokeStatement: {
				throw "POKE is not yet implemented";
			}
			case StatementType.PrintStatement: {
				return processPRINT(PrintStatement stmt);
			}
			case StatementType.RemStatement: {
				return 0;
			}
			case StatementType.ReturnStatement: {
				return processRETURN(ReturnStatement stmt);
			}
		}

		return 0;
	}

	private string processBinaryExpression(BinaryExpression exp) const throws {
		//print("processBinaryExpression(" + exp.toString() + ")");

		// determine if anyone of the expressions is a string
		bool isStringExp = exp.isString();

		// evaluate left expression
		string left = processExpression(exp.mLeft);
		string right = processExpression(exp.mRight);

		//print("BinaryExpression: " + left + " " + exp.mOperator + " " + right);

		switch ( exp.mOperator ) {
			case "+": {
				if ( isStringExp ) {
					return left + right;
				}
				return "" + ((float left) + (float right));
			}
			case "-": {
				if ( isStringExp ) {
					throw new ArithmeticException("strings not supported");
				}
				return "" + ((float left) - (float right));
			}
			case "*": {
				if ( isStringExp ) {
					throw new ArithmeticException("strings not supported");
				}
				return "" + ((float left) * (float right));
			}
			case "/": {
				if ( isStringExp ) {
					throw new ArithmeticException("strings not supported");
				}
				return "" + ((float left) / (float right));
			}
			case "%": {
				if ( isStringExp ) {
					throw new ArithmeticException("strings not supported");
				}
				return "" + ((int left) % (int right));
			}
		}

		throw "invalid binary operator '" + exp.mOperator + "'!";
	}

	private string processBooleanBinaryExpression(BinaryExpression exp) const throws {
		//print("processBooleanBinaryExpression(" + exp.toString() + ")");

		// determine if anyone of the expressions is a string
		bool isStringExp = exp.isString();

		// evaluate left expression
		string left = processExpression(exp.mLeft);
		string right = processExpression(exp.mRight);

		//print("BinaryExpression: " + left + " " + exp.mOperator + " " + right);

		switch ( exp.mOperator ) {
			case "=": {
				return "" + (left == right);
			}
			case "<": {
				if ( isStringExp ) {
					return "" + (left < right);
				}
				return "" + ((float left) < (float right));
			}
			case "<=": {
				if ( isStringExp ) {
					return "" + (left <= right);
				}
				return "" + ((float left) <= (float right));
			}
			case ">": {
				if ( isStringExp ) {
					return "" + (left > right);
				}
				return "" + ((float left) > (float right));
			}
			case ">=": {
				if ( isStringExp ) {
					return "" + (left >= right);
				}
				return "" + ((float left) >= (float right));
			}
			case "<>": {
				return "" + (left != right);
			}
		}

		throw "invalid binary operator '" + exp.mOperator + "'!";
	}

	private bool processBooleanExpression(Expression exp) const {
		//print("processBooleanExpression(" + exp.toString() + ")");

		string result = processExpression(exp);

		return result && result != "0";
	}

	private string processConstNumberExpression(ConstNumberExpression exp) const {
		//print("processConstNumberExpression(" + exp.toString() + ")");

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
			case ExpressionType.BooleanBinaryExpression: {
				return processBooleanBinaryExpression(BinaryExpression exp);
			}
			case ExpressionType.ConstNumberExpression: {
				return processConstNumberExpression(ConstNumberExpression exp);
			}
			case ExpressionType.ConstStringExpression: {
				return processConstStringExpression(ConstStringExpression exp);
			}
			case ExpressionType.FunctionExpression: {
				return processFunctionExpression(FunctionExpression exp);
			}
			case ExpressionType.UnaryExpression: {
				return processUnaryExpression(UnaryExpression exp);
			}
			case ExpressionType.VariableExpression: {
				return processVariableExpression(VariableExpression exp);
			}
		}

		throw "Unhandled expression found!";
	}

	private string processFunctionExpression(FunctionExpression exp) const throws {
		print("processFunctionExpression(" + exp.toString() + ")");

		switch ( exp.mName ) {
			case "ABS": { return functionABS(exp); }
			case "POW": { return functionPOW(exp); }
			case "SQR": { return functionSQR(exp); }
		}

		return "";
	}

	private string processUnaryExpression(UnaryExpression exp) const throws {
		//print("processUnaryExpression(" + exp.toString() + ")");

		return exp.mOperator + processExpression(exp.mExpression);
	}

	private string processVariableExpression(VariableExpression exp) const throws {
		//print("processVariableExpression(" + exp.toString() + ")");

		if ( !mVariables.contains(exp.mVariable) ) {
			throw new Exception("Unknown variable '" + exp.mVariable + "' referenced!");
		}

		return string mVariables.get(exp.mVariable);
	}

	private int processDIM(DimStatement stmt) modify throws {
		assert(stmt);

		if ( mVariables.contains(stmt.mVariable) ) {
			throw new Exception("duplicate variable '" + stmt.mVariable + "' declared!");
		}

		var obj = new String("0");

		if ( stmt.mExpression ) {
			obj = processExpression(stmt.mExpression);
		}

		mVariables.insert(stmt.mVariable, obj);

		return stmt.mFollowingStatement ? process(stmt.mFollowingStatement) : 0;
	}

	private int processEND(EndStatement stmt) const throws {
		print("END");

		if ( stmt.mFollowingStatement ) {
			throw "END does not support following statements!";
		}

		throw ControlFlow.Exit;
	}

	private int processFOR(ForStatement stmt) modify throws {
		assert( stmt );

		String obj;

		if ( !mForStack.contains(stmt.mLoopVariable.mVariable) ) {
			mForStack.insert(stmt.mLoopVariable.mVariable, mCurrentLine);

			if ( !mVariables.contains(stmt.mLoopVariable.mVariable) ) {
				mVariables.insert(stmt.mLoopVariable.mVariable, new String("0"));
			}

			obj = mVariables.get(stmt.mLoopVariable.mVariable);
			obj = processExpression(stmt.mStartExpression);
		}
		else {
			obj = mVariables.get(stmt.mLoopVariable.mVariable);
			obj = processExpression(stmt.mStepExpression);
		}

		if ( !processBooleanExpression(stmt.mTargetExpression) ) {
			mForStack.remove(stmt.mLoopVariable.mVariable);
		}

		return 0;
	}

	private int processGOSUB(GotoStatement stmt) modify throws {
		assert(stmt);

		if ( stmt.mFollowingStatement ) {
			throw "GOTO does not support following statements!";
		}

		var line = mLines.get(mCurrentLine);
		if ( line ) {
			mReturnStack.push(line.nextLine());
		}

		return stmt.mLine;
	}

	private int processGOTO(GotoStatement stmt) const throws {
		assert(stmt);

		if ( stmt.mFollowingStatement ) {
			throw "GOTO does not support following statements!";
		}

		return stmt.mLine;
	}

	private int processIF(IfStatement stmt) modify {
		assert(stmt);

		if ( processBooleanExpression(stmt.mExpression) ) {
			return process(stmt.mThenBlock);
		}

		return stmt.mFollowingStatement ? process(stmt.mFollowingStatement) : 0;
	}

	private int processINPUT(InputStatement stmt) modify throws {
		assert(stmt);

		write(stmt.mText);

		if ( !mVariables.contains(stmt.mVariable) ){
			throw new Exception("Unknown variable '" + stmt.mVariable + "' referenced!");
		}

		String obj = mVariables.get(stmt.mVariable);
		obj = cin();

		return stmt.mFollowingStatement ? process(stmt.mFollowingStatement) : 0;
	}

	private int processLET(LetStatement stmt) modify throws {
		assert(stmt);

		if ( !mVariables.contains(stmt.mVariable) ){
			throw new Exception("Unknown variable '" + stmt.mVariable + "' referenced!");
		}

		String obj = mVariables.get(stmt.mVariable);
		if ( !obj ) {
			throw "invalid variable '" + stmt.mVariable + "' referenced!";
		}

		obj = processExpression(stmt.mExpression);

		return stmt.mFollowingStatement ? process(stmt.mFollowingStatement) : 0;
	}

	private int processNEXT(NextStatement stmt) modify throws {
		assert(stmt);

		if ( mForStack.contains(stmt.mLoopVariable) ) {
			return mForStack.get(stmt.mLoopVariable);
		}

		return 0;
	}

	private int processPRINT(PrintStatement stmt) modify {
		assert(stmt);

		print(processExpression(stmt.mExpression));

		return stmt.mFollowingStatement ? process(stmt.mFollowingStatement) : 0;
	}

	private int processRETURN(ReturnStatement stmt) modify {
		assert(stmt);

		var line = mReturnStack.peek();
		mReturnStack.pop();

		return line;
	}

	//////////////////////////////////////////////////////

	private string functionABS(FunctionExpression exp) const throws {
		print("functionABS(" + exp.toString() + ")");

		if ( exp.mParameters.size() != 1 ) {
			throw new RuntimeException("invalid number of parameters for function ABS()");
		}

		var param1 = float processExpression(exp.mParameters.at(0));
		print("param1 = '" + param1 + "'");

		return "" + (param1 >= 0 ? param1 : param1 * -1);
	}

	private string functionPOW(FunctionExpression exp) const throws {
		print("functionPOW(" + exp.toString() + ")");

		if ( exp.mParameters.size() != 2 ) {
			throw new RuntimeException("invalid number of parameters for function POW()");
		}

		var param1 = float processExpression(exp.mParameters.at(0));
		print("param1 = '" + param1 + "'");

		var param2 = float processExpression(exp.mParameters.at(0));
		print("param2 = '" + param2 + "'");

		return "" + param1 * param2;
	}

	private string functionSQR(FunctionExpression exp) const throws {
		print("functionSQR(" + exp.toString() + ")");

		if ( exp.mParameters.size() != 1 ) {
			throw new RuntimeException("invalid number of parameters for function SQR()");
		}

		var param1 = float processExpression(exp.mParameters.at(0));
		print("param1 = '" + param1 + "'");

		return "" + param1 * param1;
	}


	protected int mCurrentLine;
	protected Map<string, int> mForStack;
	protected Map<int, Line> mLines;
	protected Stack<int> mReturnStack;
	protected Map<string, String> mVariables;
}

