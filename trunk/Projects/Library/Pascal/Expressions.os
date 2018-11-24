
// library imports

// project imports
import Nodes;
import Token;


public enum ExpressionType {
	BinaryExpression,
	BooleanBinaryExpression,
	ConstBooleanExpression,
	ConstIntegerExpression,
	ConstStringExpression,
	UnaryExpression,
	VariableExpression
	;
}


public abstract object Expression extends Node {
	public ExpressionType mExpressionType const;
	public Position mPosition const;

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

	public void Constructor(Token token, Expression left const, string op, Expression right const) {
		base.Constructor(ExpressionType.BinaryExpression, token);

		mLeft = left;
		mOperator = op;
		mRight = right;
	}

	public string toString() const {
		return "BinaryExpression(" + mLeft.toString() + ", '" + mOperator + "', " + mRight.toString() + ")";
	}
}

public object BooleanBinaryExpression extends BinaryExpression {
	public void Constructor(Token token, Expression left const, string op, Expression right const) {
		base.Constructor(token, left, op, right);

		mExpressionType = ExpressionType.BooleanBinaryExpression;
	}

	public string toString() const {
		return "BooleanBinaryExpression(" + mLeft.toString() + ", '" + mOperator + "', " + mRight.toString() + ")";
	}
}

public object ConstBooleanExpression extends Expression {
	public bool mValue const;

	public void Constructor(Token token, bool value) {
		base.Constructor(ExpressionType.ConstBooleanExpression, token);

		mValue = value;
	}

	public string toString() const {
		return "ConstBooleanExpression(" + mValue + ")";
	}
}

public object ConstIntegerExpression extends Expression {
	public int mValue const;

	public void Constructor(Token token, int value) {
		base.Constructor(ExpressionType.ConstIntegerExpression, token);

		mValue = value;
	}

	public string toString() const {
		return "ConstIntegerExpression(" + mValue + ")";
	}
}

public object ConstStringExpression extends Expression {
	public string mValue const;

	public void Constructor(Token token, string value) {
		base.Constructor(ExpressionType.ConstStringExpression, token);

		mValue = value;
	}

	public string toString() const {
		return "ConstStringExpression(\"" + mValue + "\")";
	}
}

public object UnaryExpression extends Expression {
	public Expression mExpression const;
	public string mOperator const;

	public void Constructor(Token token, string op, Expression exp const) {
		base.Constructor(ExpressionType.UnaryExpression, token);

		mExpression = exp;
		mOperator = op;
	}

	public string toString() const {
		return "UnaryExpression(" + mOperator + "', " + mExpression.toString() + ")";
	}
}

public object VariableExpression extends Expression {
	public string mVariable const;

	public void Constructor(Token token, string variable) {
		base.Constructor(ExpressionType.VariableExpression, token);

		mVariable = variable;
	}

	public string toString() const {
		return "VariableExpression(\"" + mVariable + "\")";
	}
}

