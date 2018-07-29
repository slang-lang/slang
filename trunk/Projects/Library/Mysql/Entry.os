
// Library imports

// Project imports

public namespace Mysql { }

public object MysqlEntry {
	private int mIndex;
	private string mName;
	private string mValue;

	public void Constructor() {
		Constructor(-1, "null", "null");
	}

	public void Constructor(string _name, string _value) {
		Constructor(-1, _name, _value);
	}

	public void Constructor(int _index, string _name, string _value) {
		mIndex = _index;
		mName = _name;
		mValue = _value;
	}

	public int index() const {
		return mIndex;
	}

	public string name() const {
		return mName;
	}

	public string value() const {
		return mValue;
	}

	public bool operator==(int _index) const {
		return mIndex == _index;
	}

	public bool operator==(string _name) const {
		return mName == _name;
	}
}

