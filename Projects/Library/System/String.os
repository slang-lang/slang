
public object String
{
	private string mValue;

	public void String(string value = "") {
		mValue = value;
	}

	public string At(int index) const {
		return substr(mValue, index, 1);
	}

	public bool EndsWith(string str) const {
		int strLength = strlen(str);
		string end = substr(mValue, strlen(mValue) - strLength, strLength);
		return str == end;
	}

	public int Size() const {
		return strlen(mValue);
	}

	public bool StartsWith(string str) const {
		string start = substr(mValue, 0, strlen(str));
		return str == start;
	}

	public string SubString(int start) const {
		return substr(mValue, start);
	}

	public string SubString(int start, int length) const {
		return substr(mValue, start, length);
	}

	public string ToLowerCase() const {
		return toLower(mValue);
	}

	public string ToString() const {
		return (string mValue);
	}

	public string ToUpperCase() const {
		return toUpper(mValue);
	}

	public string Value() const {
		return mValue;
	}
	public void Value(string value) modify {
		mValue = value;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(string other) const {
		return (mValue == other);
	}
	public bool operator==(String other) const {
		return (mValue == other.mValue);
	}

	public void operator=(string other) modify {
		mValue = other;
	}
	public void operator=(String other) modify {
		mValue = other.mValue;
	}

	public void operator+(string other) modify {
		mValue = mValue + other;
	}
	public void operator+(String other) modify {
		mValue = mValue + other.mValue;
	}
}

