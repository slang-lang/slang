
// library imports
import System.Collections.Map;

// project imports
import Line;


public enum ControlFlow {
	Exit,
	Normal;
}

public object Interpreter {
	private Map<int, Line> mLines;

	public void Constructor(Object lines) {
		assert(lines is Map<int, Line>);

		mLines = Map<int, Line> lines;
	}

	private int process(Line line) const {
		return process(line.mStatement);
	}

	private int process(Statement stmt) const throws {
		//print("process(" + stmt.toString() + ")");

		switch ( true ) {
			case stmt is DimStatement: {
				throw new Exception("DIM statement not supported!");
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
			case stmt is PrintStatement: {
				return processPRINT(PrintStatement stmt);
			}
		}

		return 0;
	}

	private bool processBooleanExpression(Expression exp) const {
		print("processBooleanExpression(" + exp.toString() + ")");

		return false;
	}

	private int processEND(EndStatement stmt) const throws {
		throw ControlFlow.Exit;
	}

	private int processGOTO(GotoStatement stmt) const {
		assert(stmt);

		return stmt.mLine;
	}

	private int processIF(IfStatement stmt) const {
		assert(stmt);

		bool isValid = processBooleanExpression(stmt.mExpression);
		if ( isValid ) {
			return process(stmt.mIfBlock);
		}

		return 0;
	}

	private int processPRINT(PrintStatement stmt) const {
		assert(stmt);

		print(stmt.mText);

		return 0;
	}

	public int run() const throws {
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

