
// library imports
import System.Collections.List;

// project imports
import Nodes;


public enum ExpressionType {
	BinaryExpression = 0,
	ConstNumberExpression,
	ConstStringExpression,
	FunctionExpression,
	VariableExpression;
}


public object Expression extends Node {
	public ExpressionType mExpressionType const;

	public void Constructor(ExpressionType expressionType) {
		base.Constructor(NodeType.ExpressionNode);

		mExpressionType = expressionType;
	}

	public abstract bool isString() const;

	public abstract string toPrettyString() const;

	public string toString() const {
		return "Epression: " + string mExpressionType;
	}
}


public object BinaryExpression extends Expression {
	public Expression mLeft const;
	public string mOperator const;
	public Expression mRight const;

	public void Constructor(Expression left const, string op, Expression right const) {
		base.Constructor(ExpressionType.BinaryExpression);

		mLeft = left;
		mOperator = op;
		mRight = right;
	}

	public bool isString() const {
		return mLeft.isString() || mRight.isString();
	}

	public string toPrettyString() const {
		return mLeft.toPrettyString() + " " + mOperator + " " + mRight.toPrettyString();
	}

	public string toString() const {
		return "BinaryExpression(" + mLeft.toString() + ", '" + mOperator + "', " + mRight.toString() + ")";
	}
}

public object ConstNumberExpression extends Expression {
	public float mValue const;

	public void Constructor(float value) {
		base.Constructor(ExpressionType.ConstNumberExpression);

		mValue = value;
	}

	public bool isString() const {
		return false;
	}

	public string toPrettyString() const {
		return string mValue;
	}

	public string toString() const {
		return "ConstNumberExpression(" + mValue + ")";
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

	public string toPrettyString() const {
		return "\"" + mValue + "\"";
	}

	public string toString() const {
		return "ConstStringExpression('" + mValue + "')";
	}
}

public object FunctionExpression extends Expression {
	public string mName const;
	public List<Expression> mParameters;

	public void Constructor(string name) {
		base.Constructor(ExpressionType.FunctionExpression);

		mName = name;
		mParameters = new List<Expression>();
	}

	public bool istString() const {
		return false;
	}

	public string toPrettyString() const {
		string params;

		foreach ( Expression exp : mParameters ) {
			if ( params ) {
				params += ", ";
			}

			params += exp.toPrettyString();
		}

		return mName + "(" + params + ")";
	}

	public string toString() const {
		string params;

		foreach ( Expression exp : mParameters ) {
			if ( params ) {
				params += ", ";
			}

			params += exp.toString();
		}

		return "FunctionExpression(" + mName + "(" + params + ")" + ")";
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

	public string toPrettyString() const {
		return mVariable;
	}

	public string toString() const {
		return "VariableExpression(" + mVariable + ")";
	}
}

