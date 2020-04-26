
// library imports
import System.Collections.List;
import System.String;

// project imports
import Expressions;


public enum StatementType {
	AssignmentStatement,
	BreakStatement,
	CaseStatement,
	CompoundStatement,
	ConstantDeclarationStatement,
	ContinueStatement,
	DeclarationStatement,
	ExitStatement,
	ForStatement,
	FunctionStatement,
	IfStatement,
	MethodCallStatement,
	ProcedureStatement,
	ProgramStatement,
	ReadlineStatement,
	RepeatStatement,
	UnitStatement,
	UsesStatement,
	VariableDeclarationStatement,
	WhileStatement,
	WriteStatement
	;
}

public object Statement extends Node {
	public StatementType mStatementType const;

	public void Constructor(StatementType statementType) {
		base.Constructor(NodeType.StatementNode);

		mStatementType = statementType;
	}

	public abstract string toString() const;
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

public object BreakStatement extends Statement {
	public void Constructor() {
		base.Constructor(StatementType.BreakStatement);
	}

	public string toString() const {
		return "BREAK";
	}
}

public object CasePart {
	public List<Expression> mExpressions;
	public Statement mStatement;
	public string mType const;

	public void Constructor(string type) {
		mExpressions = new List<Expression>();
		mType = type;
	}

	public string toString() const {
		string result;
		foreach ( Expression exp : mExpressions ) {
			if ( result ) {
				result += ", ";
			}
			result += exp.toString();
		}
		return result + ": " + mStatement ? mStatement.toString() : "";
	}
}

public object CaseStatement extends Statement {
	public List<CasePart> mCaseParts;
	public Statement mElseStatement;
	public Expression mExpression const;

	public void Constructor(Expression exp) {
		base.Constructor(StatementType.CaseStatement);

		mCaseParts = new List<CasePart>();
		mExpression = exp;
	}

	public string toString() const {
		string result;
		foreach ( CasePart part : mCaseParts ) {
			result += part.toString() + ";" + LINEBREAK;
		}
		return "CASE " + mExpression.toString() + " OF" + LINEBREAK + result + (mElseStatement ? "ELSE " + mElseStatement.toString() + ";" + LINEBREAK : "") + "END";
	}
}

public object CompoundStatement extends Statement {
	public ConstantDeclarationStatement mConstantDeclarations const;
	public List<ScopeStatement> mMethods;
	public List<Statement> mStatements const;
	public VariableDeclarationStatement mVariableDeclarations const;

	public void Constructor(List<Statement> statements) {
		base.Constructor(StatementType.CompoundStatement);

		mStatements = List<Statement> statements;
	}

	public string toString() const {
		string result;

		result += mConstantDeclarations ? mConstantDeclarations.toString() + LINEBREAK : "";
		result += mVariableDeclarations ? mVariableDeclarations.toString() + LINEBREAK : "";
		foreach ( ScopeStatement method : mMethods ?: new List<ScopeStatement>() ) {
			result += method ? method.toString() + ";" + LINEBREAK : "";
		}
		result += "BEGIN" + LINEBREAK;
		foreach ( Statement stmt : mStatements ) {
			result += stmt ? stmt.toString() + ";" + LINEBREAK : "";
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
		string result;
		foreach ( DeclarationStatement stmt : mDeclarations ) {
			result += (result ? LINEBREAK : "") + stmt.toString();
		}
		return result ? "CONST" + LINEBREAK + result : "";
	}
}

public object ContinueStatement extends Statement {
	public void Constructor() {
		base.Constructor(StatementType.ContinueStatement);
	}

	public string toString() const {
		return "CONTINUE";
	}
}

public object DeclarationStatement extends Statement {
	public bool mIsConst const;
	public string mName const;
	public string mType const;
	public Expression mValue const;

	public void Constructor(string name, string type, Expression value, bool isConst) {
		base.Constructor(StatementType.DeclarationStatement);

		mIsConst = isConst;
		mName = name;
		mType = type;
		mValue = value;
	}

	public string toString() const {
		return (mIsConst ? "CONST " : "") + mName + ": " + mType + (mValue ? " := " + mValue.toString() : "") + ";";
	}
}

public object ExitStatement extends Statement {
	public Expression mReturnValue const;

	public void Constructor(Expression returnValue) {
		base.Constructor(StatementType.ExitStatement);

		mReturnValue = returnValue;
	}

	public string toString() const {
		return "EXIT";
	}
}

public object ForStatement extends Statement {
	public Statement mBody const;
	public VariableExpression mLoopVariable const;
	public Expression mStartExpression const;
	public Expression mStepExpression const;
	public Expression mTargetExpression const;

	public void Constructor(VariableExpression variable, Expression startExpression, Expression targetExpression, Expression stepExpression, Statement body) {
		base.Constructor(StatementType.ForStatement);

		mBody = body;
		mLoopVariable = variable;
		mStartExpression = startExpression;
		mStepExpression = stepExpression;
		mTargetExpression = targetExpression;
	}

	public string toString() const {
		return "FOR " + mLoopVariable.toString() + " := " + mStartExpression.toString() + " TO " + mTargetExpression.toString() + " STEP " + (mStepExpression ? mStepExpression.toString() : "1") + LINEBREAK + mBody.toString();
	}
}

public object FunctionStatement extends ScopeStatement {
	public string mResultType const;

	public void Constructor(string name, string resultType) {
		base.Constructor(StatementType.FunctionStatement);

		mName = name;
		mResultType = resultType;
	}

	public string toString() const {
		string params;
		foreach ( DeclarationStatement stmt : mParameters ) {
			if ( params ) {
				params += " ";
			}
			params += stmt.toString();
		}

		return "FUNCTION " + mName + "(" + params + "): " + mResultType + ";" + LINEBREAK + mBody.toString();
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
	public List<Expression> mParameters;
	public string mType const;

	public void Constructor(string name, ScopeStatement method) {
		base.Constructor(StatementType.MethodCallStatement);

		mMethod = method;
		mName = name;
	}

	public string toString() const {
		string params;
		foreach ( Expression exp : mParameters ) {
			if ( params ) {
				params += ", ";
			}
			params += exp.toString();
		}
		return mName + "(" + params + ")";
	}
}

public object ProcedureStatement extends ScopeStatement {
	public void Constructor(string name) {
		base.Constructor(StatementType.ProcedureStatement);

		mName = name;
	}

	public string toString() const {
		string params;
		foreach ( DeclarationStatement stmt : mParameters ) {
			if ( params ) {
				params += " ";
			}
			params += stmt.toString();
		}

		return "PROCEDURE " + mName + "(" + params + ");" + LINEBREAK + mBody.toString();
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

public object ReadlineStatement extends Statement {
	public VariableExpression mVariable const;

	public void Constructor(VariableExpression variable) {
		base.Constructor(StatementType.ReadlineStatement);

		mVariable = variable;
	}

	public string toString() const {
		return "READLN( " + mVariable.toString() + " )";
	}
}

public object RepeatStatement extends Statement {
	public Expression mCondition const;
	public List<Statement> mStatements const;

	public void Constructor(List<Statement> statements, Expression condition) {
		base.Constructor(StatementType.RepeatStatement);

		mCondition = condition;
		mStatements = List<Statement> statements;
	}

	public string toString() const {
		string stmts;
		if ( mStatements ) {
			foreach ( Statement stmt : mStatements ) {
				stmts += stmt.toString() + LINEBREAK;
			}
		}
		return "REPEAT" + LINEBREAK + stmts + "UNTIL " + mCondition.toString();
	}
}

public object ScopeStatement extends Statement {
	public CompoundStatement mBody;
	public string mName const;
	public List<DeclarationStatement> mParameters;

	public void Constructor(StatementType statementType) {
		base.Constructor(statementType);

		mParameters = new List<DeclarationStatement>();
	}

	public abstract string toString() const;
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

		return result ? "USES " + result + ";" : "";
	}
}

public object VariableDeclarationStatement extends Statement {
	public List<DeclarationStatement> mDeclarations;

	public void Constructor() {
		base.Constructor(StatementType.ConstantDeclarationStatement);

		mDeclarations = new List<DeclarationStatement>();
	}

	public string toString() const {
		string result;
		foreach ( DeclarationStatement stmt : mDeclarations ) {
			result += (result ? LINEBREAK : "") + stmt.toString();
		}
		return result ? "VAR" + LINEBREAK + result : "";
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

public object WriteStatement extends Statement {
	public Expression mExpression const;
	public bool mLineBreak const;

	public void Constructor(Expression exp, bool lineBreak = true) {
		base.Constructor(StatementType.WriteStatement);

		mExpression = exp;
		mLineBreak = lineBreak;
	}

	public string toString() const {
		return (mLineBreak ? "WRITELN" : "WRITE") + "( " + (mExpression ? mExpression.toString() : "") + " )";
	}
}

