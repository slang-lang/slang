
// Library imports

// Project imports

public namespace Mysql { }

public object MysqlEntry {
// Public

	public void Constructor() {
		Constructor( -1, "", "" );
	}

	public void Constructor( string name, string value ) {
		Constructor( -1, name, value );
	}

	public void Constructor( int index, string name, string value ) {
		mIndex = index;
		mName = name;
		mValue = value;
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

	public bool operator==( int index ) const {
		return mIndex == index;
	}

	public bool operator==( string name ) const {
		return mName == name;
	}

// Private

	private int mIndex;
	private string mName;
	private string mValue;
}

