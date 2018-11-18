
// library imports
import System.Collections.List;
import System.String;

// project imports
import Expressions;


public enum StatementType {
	AssignmentStatement,
	CompoundStatement,
	ForStatement,
	IfStatement,
	MethodStatement,
	PrintStatement,
	ProgramStatement,
	UnitStatement,
	WhileStatement
	;
}

public object Statement extends Node {
	public StatementType mStatementType const;

	public void Constructor(StatementType statementType val) {
		base.Constructor(NodeType.StatementNode);

		mStatementType = statementType;
	}

	public string toString() const abstract;

	public string =operator(string) const {
		return toString();
	}
}


public object AssignmentStatement extends Statement {
	public Expression mLeft const;
	public Expression mRight const;

	public void Constructor(Expression left const, Expression right const) {
		base.Constructor(StatementType.AssignmentStatement);

		mLeft = left;
		mRight = right;
	}

	public string toString() const {
		return (mLeft ? mLeft.toString() : "") + " := " + (mRight ? mRight.toString() : "");
	}
}

public object CompoundStatement extends Statement {
	public List<Statement> mStatements const;

	//public void Constructor(List<Statement> statements) {
	public void Constructor(Object statements) {
		assert( statements is List<Statement> );

		base.Constructor(StatementType.CompoundStatement);

		mStatements = List<Statement> statements;
	}

	public string toString() const {
		string result = "BEGIN" + LINEBREAK;

		foreach ( Statement stmt : mStatements ) {
			result += stmt ? stmt.toString() : "";
		}

		return result + "END";
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

	public string toString() const {
		return "FOR " + mLoopVariable.toString() + " = " + mStartExpression.toString() +
		       " TO " + mTargetExpression.toString() +
			   " STEP " + (mStepExpression ? mStepExpression.toString() : "1");
	}
}

public object IfStatement extends Statement {
	public Expression mExpression const;
	public Statement mElseBlock const;
	public Statement mIfBlock const;

	public void Constructor(Expression exp const, Statement ifBlock const, Statement elseBlock const) {
		base.Constructor(StatementType.IfStatement);

		mElseBlock = elseBlock;
		mExpression = exp;
		mIfBlock = ifBlock;
	}

	public string toString() const {
		return "IF ( " + mExpression.toString() + " ) THEN"
		       + (mIfBlock ? LINEBREAK + mIfBlock.toString() : "")
			   + (mElseBlock ? LINEBREAK + "ELSE " + mElseBlock.toString() + LINEBREAK : "");
	}
}


public object MethodStatement extends Statement {
	public string mMethodName const;
	public List<String> mParameters;

	public void Constructor(string method) {
		base.Constructor(StatementType.MethodStatement);

		mMethodName = method;
	}

	public string toString() const {
		string result = mMethodName + "(";
		foreach ( string p : mParameters )
			result += p + " ";
 		result += ")";

		return result;
	}
}

public object PrintStatement extends Statement {
	public Expression mExpression const;

	public void Constructor(Expression exp) {
		base.Constructor(StatementType.PrintStatement);

		mExpression = exp;
	}

	public string toString() const {
		return "PRINT " + (mExpression ? mExpression.toString() : "");
	}
}

public object ProgramStatement extends Statement {
	public string mProgramName;
	public CompoundStatement mStatements;

	public void Constructor(string programName, CompoundStatement statements) {
		base.Constructor(StatementType.ProgramStatement);

		mProgramName = programName;
		mStatements = statements;
	}

	public string toString() const {
		return "PROGRAM " + mProgramName + ";" + LINEBREAK + mStatements ? mStatements.toString() : "";
	}
}

public object UnitStatement extends Statement {
	public CompoundStatement mStatements;
	public string mUnitName;

	public void Constructor(string unitName, CompoundStatement statements) {
		base.Constructor(StatementType.ProgramStatement);

		mStatements = statements;
		mUnitName = unitName;
	}

	public string toString() const {
		return "UNIT " + mUnitName + ";" + LINEBREAK + mStatements ? mStatements.toString() : "";
	}
}

