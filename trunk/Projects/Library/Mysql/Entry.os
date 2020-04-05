
// Library imports

// Project imports

public namespace Mysql { }

public object MysqlEntry {
// Public

	public void Constructor() {
		Constructor( -1, "", "" );
	}

	public void Constructor( string name_, string value_ ) {
		Constructor( -1, name_, value_ );
	}

	public void Constructor( int index_, string name_, string value_ ) {
		mIndex = index_;
		mName = name_;
		mValue = value_;
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

	public bool operator==( int index_ ) const {
		return mIndex == index_;
	}

	public bool operator==( string name_ ) const {
		return mName == name_;
	}

// Private

	private int mIndex;
	private string mName;
	private string mValue;
}

