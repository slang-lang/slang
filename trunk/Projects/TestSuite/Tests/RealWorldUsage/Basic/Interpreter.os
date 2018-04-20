
// library imports
import System.Collections.Map;
import System.String;

// project imports
import Line;


public enum ControlFlow {
	Exit,
	Normal;
}

public object Interpreter {
	private Map<int, Line> mLines;
	private Map<string, String> mVariables;

	public void Constructor(Object lines) {
		assert(lines is Map<int, Line>);

		mLines = Map<int, Line> lines;
		mVariables = new Map<string, String>();
	}

	private int process(Line line) modify {
		return process(line.mStatement);
	}

	private int process(Statement stmt) modify throws {
		//print("process(" + stmt.toString() + ")");

		switch ( true ) {
			case stmt is DimStatement: {
				return processDIM(DimStatement stmt);
			}
			case stmt is EndStatement: {
				return processEND(EndStatement stmt);
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
			case stmt is PrintStatement: {
				return processPRINT(PrintStatement stmt);
			}
		}

		return 0;
	}

	private string processBinaryExpression(BinaryExpression exp) const throws {
		//print("processBinaryExpression(" + exp.toString() + ")");

		string result = processExpression(exp.mLeft);

		switch ( exp.mOperator ) {
			// compare operators
			case "=": {
				print("result: '" + result + "' == '" + processExpression(exp.mRight) + "'");
				return "" + (result == processExpression(exp.mRight));
			}
			case "<": {
				print("result: '" + result + "' < '" + processExpression(exp.mRight) + "'");
				return "" + (result < processExpression(exp.mRight));
			}
			case "<=": {
				print("result: '" + result + "' <= '" + processExpression(exp.mRight) + "'");
				return "" + (result <= processExpression(exp.mRight));
			}
			case ">": {
				print("result: '" + result + "' > '" + processExpression(exp.mRight) + "'");
				return "" + (result > processExpression(exp.mRight));
			}
			case ">=": {
				print("result: '" + result + "' >= '" + processExpression(exp.mRight) + "'");
				return "" + (result >= processExpression(exp.mRight));
			}
			case "<>": {
				print("result: '" + result + "' <> '" + processExpression(exp.mRight) + "'");
				return "" + (result != processExpression(exp.mRight));
			}

			// arithmetic operators
			case "+": {
				return "" + ((int result) + (int processExpression(exp.mRight)));
			}
			case "-": {
				return "" + ((int result) - (int processExpression(exp.mRight)));
			}
			case "*": {
				return "" + ((int result) * (int processExpression(exp.mRight)));
			}
			case "/": {
				return "" + ((int result) / (int processExpression(exp.mRight)));
			}
			case "%": {
				return "" + ((int result) % (int processExpression(exp.mRight)));
			}
		}

		throw "invalid binary operator '" + exp.mOperator + "'!";
	}

	private bool processBooleanExpression(Expression exp) const {
		//print("processBooleanExpression(" + exp.toString() + ")");

		return processExpression(exp) > "0";
	}

	private string processConstExpression(ConstExpression exp) const {
		//print("processConstExpression(" + exp.toString() + ")");

		return string exp.mValue;
	}

	private string processExpression(Expression exp) const throws {
		//print("processExpression(" + exp.toString() + ")");

		switch ( true ) {
			case exp is BinaryExpression: {
				return processBinaryExpression(BinaryExpression exp);
			}
			case exp is ConstExpression: {
				return processConstExpression(ConstExpression exp);
			}
			case exp is VariableExpression: {
				return processVariableExpression(VariableExpression exp);
			}
		}

		throw "Unhandled expression found!";
	}

	private string processVariableExpression(VariableExpression exp) const throws {
		//print("processVariableExpression(" + exp.toString() + ")");

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

		return 0;
	}

	private int processEND(EndStatement stmt) const throws {
		print("END");

		throw ControlFlow.Exit;
	}

	private int processGOTO(GotoStatement stmt) const {
		assert(stmt);

		return stmt.mLine;
	}

	private int processIF(IfStatement stmt) modify {
		assert(stmt);

		bool isValid = processBooleanExpression(stmt.mExpression);
		if ( isValid ) {
			return process(stmt.mThenBlock);
		}

		return 0;
	}

	private int processINPUT(InputStatement stmt) const {
		assert(stmt);

		String obj = mVariables.get(stmt.mVariable);
		obj = cin();

		return 0;
	}

	private int processLET(LetStatement stmt) const throws {
		assert(stmt);

		String obj = mVariables.get(stmt.mVariable);
		if ( !obj ) {
			throw "invalid variable '" + stmt.mVariable + "' referenced!";
		}

		obj = processExpression(stmt.mExpression);

		return 0;
	}

	private int processPRINT(PrintStatement stmt) const {
		assert(stmt);

		if ( mVariables.contains(stmt.mText) ) {
			print(string mVariables.get(stmt.mText));
		}
		else {
			print(stmt.mText);
		}

		return 0;
	}

	public int run() modify throws {
		if ( !mLines || mLines.empty() ) {
			throw new Exception("no valid lines to interpret!");
		}

		print("Interpreting keywords...");

		int lineNumber = 10;
		Line line;

		while ( lineNumber > 0 ) {
			//print("lineNumber = " + lineNumber);

			line = mLines.get(lineNumber);

			lineNumber = process(line.mStatement) ?: line.nextLine();
		}

		print("Done interpreting.");

		return 0;
	}
}

