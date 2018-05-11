
// library imports

// project imports

public enum NodeType {
	ExpressionNode = 1,
	OperatorNode = 2,
	StatementNode = 3;
}

public object Node {
	public NodeType mNodeType;

	public void Constructor(NodeType type) {
		mNodeType = type;
	}

    public string toString() const {
		return "NodeType: " + string mNodeType;
	}
}
