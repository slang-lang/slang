
// library imports

// project imports
import Statements;

public object Line {
	public int mLineNumber const;
	public int mNextLineNumber;
	public Statement mStatement const;

	public void Constructor(int lineNumber, Statement statement) {
	 	mLineNumber = lineNumber;
		mStatement = statement;
	}

	public int nextLine() const {
		return mNextLineNumber;
	}

	public void nextLine(int next) modify {
		mNextLineNumber = next;
	}

	public string toPrettyString() const {
		return (string mLineNumber) + " " + mStatement.toPrettyString();
	}

	public string toString() const {
		return (string mLineNumber) + " " + mStatement.toString();
	}

	public bool operator==(int lineNumber) const {
		return mLineNumber == lineNumber;
	}

	public bool operator<(int lineNumber) const {
		return mLineNumber < lineNumber;
	}

	public string =operator(string) const {
		return mStatement.toString();
	}
}

