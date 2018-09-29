
// library imports

// project imports

public enum NodeType {
	ExpressionNode = 1,
	StatementNode = 2;
}

public object Node {
	public NodeType mNodeType const;

	public void Constructor(NodeType type val) {
		mNodeType = type;
	}

	public string toString() const {
		return "NodeType: " + string mNodeType;
	}
}
