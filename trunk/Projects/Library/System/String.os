
public object String
{
	private string mValue;

	public void String(string value = 0) {
		mValue = value;
	}

	public void FromString(string value) {
		mValue = (string value);
	}

	public string ToString() const {
		return (string mValue);
	}

	public string Value() const {
		return mValue;
	}
	public void Value(string value) modify {
		mValue = value;
	}

	public void operator=(string other) modify {
		mValue = other;
	}
	public void operator=(String other) modify {
		mValue = other.mValue;
	}

	public bool operator==(string other) const {
		return (mValue == other);
	}
	public bool operator==(String other) const {
		return (mValue == other.mValue);
	}
}

