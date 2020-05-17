
// library imports
import System.String;

// project imports
import Statements;


public object Symbol {
	public string mName const;
	public int mStackIndex const;
	public string mType const;

	public void Constructor(string name, string type) {
		mName = name;
		mType = type;
	}

	public bool operator==(string other) const {
		return mName == other;
	}

	public bool operator==(Symbol other const) const {
		return mName == other.mName;
	}

	public string =operator(string) const {
		return mName + "(" + mStackIndex + "):" + mType;
	}
}

public object LocalSymbol extends Symbol {
	public bool mIsConst const;
	public String mValue;

	public void Constructor(string name, int stackIndex, string type, bool isConst = false, String value = null) {
		base.Constructor(name, type);

		mIsConst = isConst;
		mStackIndex = stackIndex;
		mValue = value;
	}

	public string =operator(string) const {
		return (mIsConst ? "CONST " : "") + mName + "(" + mStackIndex + "): " + mType;
	}
}

public object MethodSymbol extends Symbol {
	public ScopeStatement mMethod const;

	public void Constructor(string name, int stackIndex, string type, ScopeStatement method) {
		base.Constructor(name, type);

		mMethod = method;
		mStackIndex = stackIndex;
	}
}

