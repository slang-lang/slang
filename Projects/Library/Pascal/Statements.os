
// library imports
import System.Collections.List;
import System.String;

// project imports
import Expressions;


public enum StatementType {
	AssignmentStatement,
	CompoundStatement,
	ConstantDeclarationStatement,
	ForStatement,
	FunctionStatement,
	IfStatement,
	MethodStatement,
	PrintStatement,
	ProgramStatement,
	UnitStatement,
	VariableDeclarationStatement,
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
		string result = "BEGIN ";

		foreach ( Statement stmt : mStatements ) {
			result += LINEBREAK + (stmt ? stmt.toString() : "") + ";";
		}

		return result + LINEBREAK + "END";
	}
}

public object FunctionStatement extends Statement {
	public Statement mBody const;
	public string mName const;
	public string mResultType const;

	public void Constructor(string name, string resultType, Statement body) {
		base.Constructor(StatementType.FunctionStatement);

		mBody = body;
		mName = name;
		mResultType = resultType;
	}

	public string toString() const {
		return "FUNCTION " + mName + "() : " + mResultType + " " + mBody.toString();
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
	public Expression mCondition const;
	public Statement mElseBlock const;
	public Statement mIfBlock const;

	public void Constructor(Expression exp const, Statement ifBlock const, Statement elseBlock const) {
		base.Constructor(StatementType.IfStatement);

		mCondition = exp;
		mElseBlock = elseBlock;
		mIfBlock = ifBlock;
	}

	public string toString() const {
		return "IF ( " + mCondition.toString() + " ) THEN" + LINEBREAK
		       + (mIfBlock ? mIfBlock.toString() : "")
			   + (mElseBlock ? LINEBREAK + "ELSE " + mElseBlock.toString() : "");
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
		foreach ( string p : mParameters ) {
			result += p + " ";
		}
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
		return "PRINT( " + (mExpression ? mExpression.toString() : "") + " )";
	}
}

public object ProgramStatement extends Statement {
	public string mName;
	public CompoundStatement mStatements;

	public void Constructor(string programName, CompoundStatement statements) {
		base.Constructor(StatementType.ProgramStatement);

		mName = programName;
		mStatements = statements;
	}

	public string toString() const {
		return "PROGRAM " + mName + ";" + LINEBREAK + (mStatements ? mStatements.toString() : "") + ".";
	}
}

public object UnitStatement extends Statement {
	public CompoundStatement mStatements;
	public string mName;

	public void Constructor(string unitName, CompoundStatement statements) {
		base.Constructor(StatementType.ProgramStatement);

		mName = unitName;
		mStatements = statements;
	}

	public string toString() const {
		return "UNIT " + mName + ";" + LINEBREAK + (mStatements ? mStatements.toString() : "") + ";";
	}
}

public object VariableDeclarationStatement extends Statement {
}

public object WhileStatement extends Statement {
	public Statement mBody const;
	public Expression mCondition const;

	public void Constructor(Expression condition, Statement body) {
		base.Constructor(StatementType.WhileStatement);

		mBody = body;
		mCondition = condition;
	}

	public string toString() const {
		return "WHILE " + mCondition.toString() + " " + mBody.toString();
	}
}

