
public object Boolean
{
	private bool mValue;

	public void Boolean(bool value = false) {
		mValue = value;
	}

	public void FromString(string value) {
		mValue = (bool value);
	}

	public string ToString() const {
		return (string mValue);
	}

	public bool Value() const {
		return mValue;
	}
	public void Value(bool value) modify {
		mValue = value;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(bool other) const {
		return (mValue == other);
	}
	public bool operator==(Boolean other) const {
		return (mValue == other.mValue);
	}

	public void operator=(bool other) modify {
		mValue = other;
	}
	public void operator=(Boolean other) modify {
		mValue = other.mValue;
	}
}

