
// library imports
import System.String;

// project imports
import Expressions;


public enum StatementType {
	DimStatement = 0,
	EndStatement,
	ForStatement,
	GoSubStatement,
	GotoStatement,
	IfStatement,
	InputStatement,
	LetStatement,
	MethodStatement,
	NextStatement,
	OnStatement,
	PeekStatement,
	PokeStatement,
	PrintStatement,
	RemStatement,
	ReturnStatement;
}

public object Statement extends Node {
	public Statement mFollowingStatement;
	public StatementType mStatementType const;

	public void Constructor(StatementType statementType) {
		base.Constructor(NodeType.StatementNode);

		mStatementType = statementType;
	}

	public string toPrettyString() const abstract;

	public string toString() const abstract;

	protected string following() const {
		return mFollowingStatement ? (" : " + mFollowingStatement.toString()) : "";
	}

	protected string prettyFollowing() const {
		return mFollowingStatement ? (" : " + mFollowingStatement.toPrettyString()) : "";
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

	public string toPrettyString() const {
		return "DIM " + mVariable + mExpression ? ( " = " + mExpression.toPrettyString()) : "" + prettyFollowing();
	}

	public string toString() const {
		return "DIM " + mVariable + mExpression ? (" = " + mExpression.toString()) : "" + following();
	}
}

public object EndStatement extends Statement {
	public void Constructor() {
		base.Constructor(StatementType.EndStatement);
	}

	public string toPrettyString() const {
		return "END " + prettyFollowing();
	}

	public string toString() const {
		return "END " + following();
	}
}

public object ForStatement extends Statement {
	public VariableExpression mLoopVariable const;
	public Expression mStartExpression const;
	public Expression mStepExpression const;
	public Expression mTargetExpression const;

	public void Constructor(VariableExpression variable, Expression startExpression,
							Expression targetExpression, Expression stepExpression) {
		base.Constructor(StatementType.ForStatement);

		mLoopVariable = variable;
		mStartExpression = startExpression;
		mStepExpression = stepExpression;
		mTargetExpression = targetExpression;
	}

	public string toPrettyString() const {
		return "FOR " + mLoopVariable.toPrettyString() + " = " + mStartExpression.toPrettyString() +
			   " TO " + mTargetExpression.toPrettyString() +
			   " STEP " + (mStepExpression ? mStepExpression.toPrettyString() : "1") + prettyFollowing();
	}

	public string toString() const {
		return "FOR " + mLoopVariable.toString() + " = " + mStartExpression.toString() +
		       " TO " + mTargetExpression.toString() +
			   " STEP " + (mStepExpression ? mStepExpression.toString() : "1") + following();
	}
}

public object GoSubStatement extends Statement {
	public int mLine const;

	public void Constructor(int line) {
		base.Constructor(StatementType.GoSubStatement);

		mLine = line;
	}

	public string toPrettyString() const {
		return "GOSUB " + mLine + prettyFollowing();
	}

	public string toString() const {
		return "GOSUB " + mLine + following();
	}
}

public object GotoStatement extends Statement {
	public int mLine const;

	public void Constructor(int line) {
		base.Constructor(StatementType.GotoStatement);

		mLine = line;
	}

	public string toPrettyString() const {
		return "GOTO " + mLine + prettyFollowing();
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

	public string toPrettyString() const {
		return "IF " + mExpression.toPrettyString()  + " THEN " + mThenBlock.toPrettyString() + prettyFollowing();
	}

	public string toString() const {
		return "IF " + mExpression.toString() + " THEN " + mThenBlock.toString() + following();
	}
}

public object InputStatement extends Statement {
	public string mText const;
	public string mVariable const;

	public void Constructor(string text, string variable) {
		base.Constructor(StatementType.InputStatement);

		mText = text;
		mVariable = variable;
	}

	public string toPrettyString() const {
		return "INPUT \"" + (mText ? (mText + "\" ") : "\"") + mVariable + prettyFollowing();
	}

	public string toString() const {
		return "INPUT \"" + (mText ? (mText + "\" ") : "\"") + mVariable + following();
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

	public string toPrettyString() const {
		return "LET " + mVariable + " = " + mExpression.toPrettyString() + prettyFollowing();
	}

	public string toString() const {
		return "LET " + mVariable + " = " + mExpression.toString() + following();
	}
}

public object MethodStatement extends Statement {
	public string mMethodName const;
	public List<String> mParameters;

	public void Constructor(string method) {
		base.Constructor(StatementType.MethodStatement);

		mMethodName = method;
	}

	public string toPrettyString() const {
		string result = mMethodName + "(";
		foreach ( String p : mParameters )
			result += string p + " ";
 		result += ")";

		return result + prettyFollowing();
	}

	public string toString() const {
		string result = mMethodName + "(";
		foreach ( string p : mParameters )
			result += p + " ";
 		result += ")";

		return result + following();
	}
}

public object NextStatement extends Statement {
	public string mLoopVariable;

	public void Constructor(string loopVariable) {
		base.Constructor(StatementType.NextStatement);

		mLoopVariable = loopVariable;
	}

	public string toPrettyString() const {
		return "NEXT " + mLoopVariable + prettyFollowing();
	}

	public string toString() const {
		return "NEXT " + mLoopVariable + following();
	}
}

public object OnStatement extends Statement {
	public Expression mExpression const;
	public List<int> mLines;

	public void Constructor(Expression exp) {
		base.Constructor(StatementType.OnStatement);

		mExpression = exp;
		mLines = new List<int>();
	}

	public string toPrettyString() const {
		return "ON " + mExpression.toPrettyString() + " GOTO " + prettyFollowing();
	}

	public string toString() const {
		return "ON " + mExpression.toString() + " GOTO " + following();
	}
}

public object PrintStatement extends Statement {
	public Expression mExpression const;

	public void Constructor(Expression exp) {
		base.Constructor(StatementType.PrintStatement);

		mExpression = exp;
	}

	public string toPrettyString() const {
		return "PRINT " + (mExpression ? mExpression.toPrettyString() : "") + prettyFollowing();
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

	public string toPrettyString() const {
		return "REM " + mComment + prettyFollowing();
	}

	public string toString() const {
		return "REM " + mComment + following();
	}
}

public object ReturnStatement extends Statement {
	public void Constructor() {
		base.Constructor(StatementType.ReturnStatement);
	}

	public string toPrettyString() const {
		return "RETURN";
	}

	public string toString() const {
		return "RETURN";
	}
}

