
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
	GotoStatement,
	IfStatement,
	InputStatement,
	LetStatement,
	PrintStatement,
	RemStatement;
}

public object Statement extends Node {
	public StatementType mStatementType const;

	public void Constructor(StatementType statementType) {
		base.Constructor(NodeType.StatementNode);

		mStatementType = statementType;
	}

	public string toString() const {
		return "Statement: " + string mStatementType;
	}
}


public object DimStatement extends Statement {
	public string mVariable const;

	public void Constructor(string variable) {
		base.Constructor(StatementType.DimStatement);

		mVariable = variable;
	}

	public string toString() const {
		return "DIM " + mVariable;
	}
}

public object EndStatement extends Statement {
	public void Constructor() {
		base.Constructor(StatementType.EndStatement);
	}

	public string toString() const {
		return "END";
	}
}

public object GotoStatement extends Statement {
	public int mLine const;

	public void Constructor(int line) {
		base.Constructor(StatementType.GotoStatement);

		mLine = line;
	}

	public string toString() const {
		return "GOTO " + mLine;
	}
}

public object IfStatement extends Statement {
	public Expression mExpression const;
	public Statement mThenBlock const;

	public void Constructor(Expression exp, Statement thenBlock) {
		base.Constructor(StatementType.IfStatement);

		mExpression = exp;
		mThenBlock = thenBlock;
	}

	public string toString() const {
		return "IF " + mExpression.toString() + " THEN " + mThenBlock.toString();
	}
}

public object InputStatement extends Statement {
	public string mVariable const;

	public void Constructor(string variable) {
		base.Constructor(StatementType.InputStatement);

		mVariable = variable;
	}

	public string toString() const {
		return "INPUT " + mVariable;
	}
}

public object LetStatement extends Statement {
	public Expression mExpression const;
	public string mVariable const;

	public void Constructor(string variable, Expression exp) {
		base.Constructor(StatementType.LetStatement);

		mExpression = exp;
		mVariable = variable;
	}

	public string toString() const {
		return "LET " + mVariable + " = " + mExpression.toString();
	}
}

public object PrintStatement extends Statement {
	public string mText const;

	public void Constructor(string text) {
		base.Constructor(StatementType.PrintStatement);

		mText = text;
	}

	public string toString() const {
		return "PRINT " + mText;
	}
}

public object RemStatement extends Statement {
	public string mComment const;

	public void Constructor(string text = "") {
		base.Constructor(StatementType.RemStatement);

		mComment = text;
	}

	public string toString() const {
		//return "REM " + mComment;
		return "REM";
	}
}

