
// library imports

// project imports
import Nodes;


public enum ExpressionType {
	BinaryExpression = 0,
	ConstIntegerExpression,
	ConstStringExpression,
	VariableExpression;
}


public abstract object Expression extends Node {
	public ExpressionType mExpressionType const;

	public void Constructor(ExpressionType expressionType) {
		base.Constructor(NodeType.ExpressionNode);

		mExpressionType = expressionType;
	}

	public bool isString() const abstract;

	public string toString() const {
		return "Epression: " + string mExpressionType;
	}
}


public object BinaryExpression extends Expression {
	public Expression mLeft const;
	public string mOperator const;
	public Expression mRight const;

	public void Constructor(string op) {
		base.Constructor(ExpressionType.BinaryExpression);

		mOperator = op;
	}

	public bool isString() const {
		return mLeft.isString() || mRight.isString();
	}

	public string toString() const {
		return "BinaryExpression(" + mLeft.toString() + ", '" + mOperator + "', " + mRight.toString() + ")";
	}
}

public object ConstIntegerExpression extends Expression {
	public int mValue const;

	public void Constructor(int value) {
		base.Constructor(ExpressionType.ConstIntegerExpression);

		mValue = value;
	}

	public bool isString() const {
		return false;
	}

	public string toString() const {
		return "ConstIntegerExpression(" + mValue + ")";
	}
}

public object ConstStringExpression extends Expression {
	public string mValue const;

	public void Constructor(string value) {
		base.Constructor(ExpressionType.ConstStringExpression);

		mValue = value;
	}

	public bool isString() const {
		return true;
	}

	public string toString() const {
		return "ConstStringExpression(" + mValue + ")";
	}
}

public object VariableExpression extends Expression {
	public string mVariable const;

	public void Constructor(string variable) {
		base.Constructor(ExpressionType.VariableExpression);

		mVariable = variable;
	}

	public bool isString() const {
		return false;
	}

	public string toString() const {
		return "VariableExpression(" + mVariable + ")";
	}
}

