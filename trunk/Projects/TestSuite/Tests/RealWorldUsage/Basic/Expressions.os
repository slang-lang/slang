
// library imports

// project imports
import Nodes;


public enum ExpressionType {
	BinaryExpression = 0;
}


public object Expression extends Node {
	public int mExpressionType;

	public void Constructor(int expressionType) {
		base.Constructor(NodeType.ExpressionNode);

		mExpressionType = expressionType;
	}

	public string toString() const {
		return "Epression: " + string mExpressionType;
	}
}

