
// library imports
import System.Collections.List;
import System.String;

// project imports
import Expressions;


public enum StatementType {
	AssignmentStatement,
	CompoundStatement,
	ConstantDeclarationStatement,
	DeclarationStatement,
	ForStatement,
	FunctionStatement,
	IfStatement,
	MethodCallStatement,
	PrintStatement,
	ProcedureStatement,
	ProgramStatement,
	UnitStatement,
	UsesStatement,
	VariableDeclarationStatement,
	WhileStatement
	;
}

public object Statement extends Node {
	public StatementType mStatementType const;

	public void Constructor(StatementType statementType) {
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
	public ConstantDeclarationStatement mConstantDeclarations const;
	public List<ScopeStatement> mMethods;
	public List<Statement> mStatements const;
	public VariableDeclarationStatement mVariableDeclarations const;

	//public void Constructor(List<Statement> statements) {
	public void Constructor(Object statements) {
		assert( statements is List<Statement> );

		base.Constructor(StatementType.CompoundStatement);

		mStatements = List<Statement> statements;
	}

	public string toString() const {
		string result = mConstantDeclarations ? mConstantDeclarations.toString() + LINEBREAK : "";
		result += mVariableDeclarations ? mVariableDeclarations.toString() + LINEBREAK : "";
		foreach ( ScopeStatement method : mMethods ?: new List<ScopeStatement>() ) {
			result += (method ? method.toString() : "") + ";" + LINEBREAK;
		}
		result += "BEGIN" + LINEBREAK;
		foreach ( Statement stmt : mStatements ) {
			result += (stmt ? stmt.toString() + ";" + LINEBREAK : "");
		}
		return result + "END";
	}
}

public object ConstantDeclarationStatement extends Statement {
	public List<DeclarationStatement> mDeclarations;

	public void Constructor() {
		base.Constructor(StatementType.ConstantDeclarationStatement);

		mDeclarations = new List<DeclarationStatement>();
	}

	public string toString() const {
		if ( mDeclarations.empty() ) {
			return "";
		}

		string result;
		foreach ( DeclarationStatement stmt : mDeclarations ) {
			result += (result ? LINEBREAK : "") + stmt.toString();
		}

		return "CONST" + LINEBREAK + result;
	}
}

public object DeclarationStatement extends Statement {
	public string mName const;
	public string mType const;
	public Expression mValue const;

	public void Constructor(string name, string type, Expression value) {
		base.Constructor(StatementType.DeclarationStatement);

		mName = name;
		mType = type;
		mValue = value;
	}

	public string toString() const {
		return mName + ": " + mType + (mValue ? " := " + mValue.toString() : "") + ";";
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

public object FunctionStatement extends ScopeStatement {
	public string mResultType const;

	public void Constructor(string name, string resultType, CompoundStatement body) {
		base.Constructor(StatementType.FunctionStatement);

		mBody = body;
		mName = name;
		mResultType = resultType;
	}

	public string toString() const {
		return "FUNCTION " + mName + "() : " + mResultType + " " + mBody.toString();
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

public object MethodCallStatement extends Statement {
	public ScopeStatement mMethod const;
	public string mName const;
	public string mType const;

	public void Constructor(string name, ScopeStatement method) {
		base.Constructor(StatementType.MethodCallStatement);

		mMethod = method;
		mName = name;
	}

	public string toString() const {
		return mName + "()";
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

public object ProcedureStatement extends ScopeStatement {
	public void Constructor(string name, CompoundStatement body) {
		base.Constructor(StatementType.ProcedureStatement);

		mBody = body;
		mName = name;
	}

	public string toString() const {
		return "PROCEDURE " + mName + "();" + LINEBREAK + mBody.toString();
	}
}

public object ProgramStatement extends Statement {
	public string mName const;
	public CompoundStatement mStatements const;
	public UsesStatement mUses const;

	public void Constructor(string name, UsesStatement uses, CompoundStatement statements) {
		base.Constructor(StatementType.ProgramStatement);

		mName = name;
		mStatements = statements;
		mUses = uses;
	}

	public string toString() const {
		string result = "PROGRAM " + mName + ";" + LINEBREAK;
		//result += mUses.toString();
		result += mStatements ? mStatements.toString() : "";

		return result + ".";
	}
}

public object ScopeStatement extends Statement {
	public CompoundStatement mBody const;
	public string mName const;

	public void Constructor(StatementType statementType) {
		base.Constructor(statementType);
	}

	public string toString() const {
		return "SCOPE " + mName + "();" + LINEBREAK + mBody.toString();
	}
}

public object UnitStatement extends Statement {
	public string mName const;
	public CompoundStatement mStatements const;
	public UsesStatement mUses const;

	public void Constructor(string name, UsesStatement uses, CompoundStatement statements) {
		base.Constructor(StatementType.UnitStatement);

		mName = name;
		mStatements = statements;
		mUses = uses;
	}

	public string toString() const {
		string result = "UNIT " + mName + ";" + LINEBREAK;
		result += mUses.toString() ?: "";
		result += mStatements ? mStatements.toString() : "";

		return result + ";";
	}
}

public object UsesStatement extends Statement {
	public List<string> mUnits;

	public void Constructor() {
		base.Constructor(StatementType.UsesStatement);

		mUnits = new List<string>();
	}

	public string toString() const {
		string result;

		foreach ( string unit : mUnits ) {
			if ( !result ) {
				result = unit;
				continue;
			}

			result += ", " + unit;
		}

		return result ? "USES " + result + ";" + LINEBREAK : "";
	}
}

public object VariableDeclarationStatement extends Statement {
	public List<DeclarationStatement> mDeclarations;

	public void Constructor() {
		base.Constructor(StatementType.ConstantDeclarationStatement);

		mDeclarations = new List<DeclarationStatement>();
	}

	public string toString() const {
		if ( mDeclarations.empty() ) {
			return "";
		}

		string result;
		foreach ( DeclarationStatement stmt : mDeclarations ) {
			result += (result ? LINEBREAK : "") + stmt.toString();
		}

		return "VAR" + LINEBREAK + result;
	}
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
		return "WHILE " + mCondition.toString() + " DO " + mBody.toString();
	}
}
