
// library imports
import System.Collections.Map;
import System.String;

// project imports
import Line;

public int FIRST_LINE const = 10;

public enum ControlFlow {
	Exit,
	Normal;
}

public object Interpreter {
	protected int mCurrentLine;
	protected Map<string, int> mForStack;
	protected Map<int, Line> mLines;
	protected Map<string, String> mVariables;

	public void Constructor(Object lines) {
		assert(lines is Map<int, Line>);

		mCurrentLine = FIRST_LINE;
		mForStack = new Map<string, int>();
		mLines = Map<int, Line> lines;
		mVariables = new Map<string, String>();
	}

	protected int process(Statement stmt) modify throws {
		//print("process(" + stmt.toString() + ")");

		switch ( true ) {
			case stmt is DimStatement: {
				return processDIM(DimStatement stmt);
			}
			case stmt is EndStatement: {
				return processEND(EndStatement stmt);
			}
			case stmt is ForStatement: {
				return processFOR(ForStatement stmt);
			}
			case stmt is GotoStatement: {
				return processGOTO(GotoStatement stmt);
			}
			case stmt is IfStatement: {
				return processIF(IfStatement stmt);
			}
			case stmt is InputStatement: {
				return processINPUT(InputStatement stmt);
			}
			case stmt is LetStatement: {
				return processLET(LetStatement stmt);
			}
			case stmt is NextStatement: {
				return processNEXT(NextStatement stmt);
			}
			case stmt is PrintStatement: {
				return processPRINT(PrintStatement stmt);
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
			// compare operators
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

			// arithmetic operators
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

		switch ( true ) {
			case exp is BinaryExpression: {
				return processBinaryExpression(BinaryExpression exp);
			}
			case exp is ConstNumberExpression: {
				return processConstNumberExpression(ConstNumberExpression exp);
			}
			case exp is ConstStringExpression: {
				return processConstStringExpression(ConstStringExpression exp);
			}
			case exp is VariableExpression: {
				return processVariableExpression(VariableExpression exp);
			}
		}

		throw "Unhandled expression found!";
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

	public int run() modify throws {
		if ( !mLines || mLines.empty() ) {
			throw new Exception("no valid lines to interpret!");
		}

		mForStack.clear();
		mVariables.clear();

		//print("Started interpreting statements...");

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

		//print("Done interpreting.");

		return 0;
	}
}

