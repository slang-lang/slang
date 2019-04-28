
// library imports

// project imports
import Nodes;
import Statements;
import Token;


public enum ExpressionType {
	BinaryExpression,
	BooleanBinaryExpression,
	ConstantExpression,
	LiteralBooleanExpression,
	LiteralIntegerExpression,
	LiteralRealExpression,
	LiteralStringExpression,
	MethodExpression,
	UnaryExpression,
	VariableExpression
	;
}


public abstract object Expression extends Node {
	public ExpressionType mExpressionType const;
	public Position mPosition const;
	public string mResultType const;

	public void Constructor(ExpressionType expressionType const, Token token) {
		base.Constructor(NodeType.ExpressionNode);

		mExpressionType = expressionType;
		mPosition = token ? token.mPosition : Position null;
	}

	public string toString() const {
		return "Epression: " + string mExpressionType;
	}
}


public object BinaryExpression extends Expression {
	public Expression mLeft const;
	public string mOperator const;
	public Expression mRight const;

	public void Constructor(Token token, Expression left const, string op, Expression right const, string resultType) {
		base.Constructor(ExpressionType.BinaryExpression, token);

		mLeft = left;
		mOperator = op;
		mRight = right;
		mResultType = resultType;
	}

	public string toString() const {
		return "BinaryExpression(" + mLeft.toString() + ", '" + mOperator + "', " + mRight.toString() + ", Type: " + mResultType + ")";
	}
}

public object BooleanBinaryExpression extends BinaryExpression {
	public void Constructor(Token token, Expression left const, string op, Expression right const) {
		base.Constructor(token, left, op, right, "BOOLEAN");

		mExpressionType = ExpressionType.BooleanBinaryExpression;
	}

	public string toString() const {
		return "BooleanBinaryExpression(" + mLeft.toString() + ", '" + mOperator + "', " + mRight.toString() + ", Type: " + mResultType + ")";
	}
}

public object ConstantExpression extends Expression {
	public string mConstant const;

	public void Constructor(Token token, string constant, string type = "INTEGER") {
		base.Constructor(ExpressionType.ConstantExpression, token);

		mConstant = constant;
		mResultType = type;
	}

	public string toString() const {
		return "ConstantExpression(\"" + mConstant + "\", Type: " + mResultType + ")";
	}
}

public object LiteralBooleanExpression extends Expression {
	public bool mValue const;

	public void Constructor(Token token, bool value) {
		base.Constructor(ExpressionType.LiteralBooleanExpression, token);

		mResultType = "BOOLEAN";
		mValue = value;
	}

	public string toString() const {
		return "LiteralBooleanExpression(" + mValue + ")";
	}
}

public object LiteralIntegerExpression extends Expression {
	public int mValue const;

	public void Constructor(Token token, int value) {
		base.Constructor(ExpressionType.LiteralIntegerExpression, token);

		mResultType = "INTEGER";
		mValue = value;
	}

	public string toString() const {
		return "LiteralIntegerExpression(" + mValue + ")";
	}
}

public object LiteralRealExpression extends Expression {
	public float mValue const;

	public void Constructor(Token token, float value) {
		base.Constructor(ExpressionType.LiteralRealExpression, token);

		mResultType = "REAL";
		mValue = value;
	}

	public string toString() const {
		return "LiteralRealExpression(" + mValue + ")";
	}
}

public object LiteralStringExpression extends Expression {
	public string mValue const;

	public void Constructor(Token token, string value) {
		base.Constructor(ExpressionType.LiteralStringExpression, token);

		mResultType = "STRING";
		mValue = value;
	}

	public string toString() const {
		return "LiteralStringExpression(\"" + mValue + "\")";
	}
}

public object MethodExpression extends Expression {
	public ScopeStatement mMethod const;

	public void Constructor(Token token, ScopeStatement method, string type = "INTEGER") {
		base.Constructor(ExpressionType.MethodExpression, token);

		mMethod = method;
		mResultType = type;
	}

	public string toString() const {
		return "MethodExpression(\"" + mMethod.mName + "\", Type: " + mResultType + ")";
	}
}

public object UnaryExpression extends Expression {
	public Expression mExpression const;
	public string mOperator const;

	public void Constructor(Token token, string op, Expression exp const) {
		base.Constructor(ExpressionType.UnaryExpression, token);

		mExpression = exp;
		mOperator = op;
		mResultType = exp.mResultType;
	}

	public string toString() const {
		return "UnaryExpression(" + mOperator + "', " + mExpression.toString() + ", Type: " + mResultType + ")";
	}
}

public object VariableExpression extends Expression {
	public string mVariable const;

	public void Constructor(Token token, string variable, string type = "INTEGER") {
		base.Constructor(ExpressionType.VariableExpression, token);

		mResultType = type;
		mVariable = variable;
	}

	public string toString() const {
		return "VariableExpression(\"" + mVariable + "\", Type: " + mResultType + ")";
	}
}

