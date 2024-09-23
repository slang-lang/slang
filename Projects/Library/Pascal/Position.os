
// library imports

// project imports


public object Position const {
	public int mColumn const;
	public int mLine const;

	public void Constructor(int line, int column) {
		mColumn = column;
		mLine = line;
	}

	public string toString() const {
		return "Position(Line " + mLine + ", Column " + mColumn + ")";
	}

	public string =operator(string) const {
		return "Line " + mLine + ", Column " + mColumn;
	}
}

