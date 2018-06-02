
// library imports

// project imports
import Expressions;


string KEYWORD_DIM const = "DIM";
int KEYWORD_DIM_ID const = 1;
string KEYWORD_GOTO const = "GOTO";
int KEYWORD_GOTO_ID const = 2;
string KEYWORD_IF const = "IF";
int KEYWORD_IF_ID const = 3;
string KEYWORD_INPUT const = "IF";
int KEYWORD_INPUT_ID const = 4;
string KEYWORD_LABEL const = "LABEL";
int KEYWORD_LABEL_ID const = 5;
string KEYWORD_PRINT const = "PRINT";
int KEYWORD_PRINT_ID const = 6;
string KEYWORD_REM const = "REM";
int KEYWORD_REM_ID const = 7;


public enum StatementType {
	DimStatement = 0,
	EndStatement,
	ForStatement,
	GotoStatement,
	IfStatement,
	InputStatement,
	LetStatement,
	PrintStatement,
	RemStatement;
}

public object Statement extends Node {
	public Statement mFollowingStatement;
	public StatementType mStatementType const;

	public void Constructor(StatementType statementType val) {
		base.Constructor(NodeType.StatementNode);

		mStatementType = statementType;
	}

	public string toString() const {
		return "Statement: " + string mStatementType;
	}

	protected string following() const {
		return mFollowingStatement ? (" : " + mFollowingStatement.toString()) : "";
	}
}


public object DimStatement extends Statement {
	public Expression mExpression const;
	public string mVariable const;

	public void Constructor(string variable, Expression exp) {
		base.Constructor(StatementType.DimStatement);

		mExpression = exp;
		mVariable = variable;
	}

	public string toString() const {
		return "DIM " + mVariable + mExpression ? (" = " + mExpression.toString()) : "" + following();
	}
}

public object EndStatement extends Statement {
	public void Constructor() {
		base.Constructor(StatementType.EndStatement);
	}

	public string toString() const {
		return "END" + following();
	}
}

public object ForStatement extends Statement {
	public int mEndValue const;
	public int mStartValue const;
	public int mStepValue const;
	public string mVariable const;

	public void Constructor(string variable, int startValue, int endValue, int stepValue = 1) {
		base.Constructor(StatementType.DimStatement);

		mEndValue = endValue;
		mStartValue = startValue;
		mStepValue = stepValue;
		mVariable = variable;
	}

	public string toString() const {
		return "FOR " + mVariable + " = " + mStartValue + " TO " + mEndValue + " STEP " + mStepValue + following();
	}
}

public object GotoStatement extends Statement {
	public int mLine const;

	public void Constructor(int line) {
		base.Constructor(StatementType.GotoStatement);

		mLine = line;
	}

	public string toString() const {
		return "GOTO " + mLine + following();
	}
}

public object IfStatement extends Statement {
	public Expression mExpression const;
	public Statement mThenBlock const;

	public void Constructor(Expression exp const, Statement thenBlock const) {
		base.Constructor(StatementType.IfStatement);

		mExpression = exp;
		mThenBlock = thenBlock;
	}

	public string toString() const {
		return "IF " + mExpression.toString() + " THEN " + mThenBlock.toString() + following();
	}
}

public object InputStatement extends Statement {
	public string mText;
	public string mVariable const;

	public void Constructor(string text, string variable) {
		base.Constructor(StatementType.InputStatement);

		mText = text;
		mVariable = variable;
	}

	public string toString() const {
		return "INPUT " + mText ? (mText + " ") : "" + mVariable;
	}
}

public object LetStatement extends Statement {
	public Expression mExpression const;
	public string mVariable const;

	public void Constructor(string variable, Expression exp const) {
		base.Constructor(StatementType.LetStatement);

		mExpression = exp;
		mVariable = variable;
	}

	public string toString() const {
		return "LET " + mVariable + " = " + mExpression.toString() + following();
	}
}

public object PrintStatement extends Statement {
	public Expression mExpression const;

	public void Constructor(Expression exp) {
		base.Constructor(StatementType.PrintStatement);

		mExpression = exp;
	}

	public string toString() const {
		return "PRINT " + (mExpression ? mExpression.toString() : "") + following();
	}
}

public object RemStatement extends Statement {
	public string mComment const;

	public void Constructor(string text = "") {
		base.Constructor(StatementType.RemStatement);

		mComment = text;
	}

	public string toString() const {
		return "REM " + mComment + following();
	}
}

