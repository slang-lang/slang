
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Boolean {
	/*
	 * Default constructor 
	 */
	public void Constructor(bool value = false) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Boolean value ref) {
		mValue = value.mValue;
	}

	/*
	 * Copy operator
	 */
	public Boolean Copy() const {
		return new Boolean(mValue);
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(bool other) const {
		return mValue == other;
	}
	public bool operator==(Boolean other ref) const {
		return mValue == other.mValue;
	}

	public Boolean operator=(bool other) modify {
		mValue = other;

		return this;
	}
	public Boolean operator=(Boolean other ref) modify {
		mValue = other.mValue;

		return this;
	}

	/*
	 * bool-value operator
	 */
	public bool =operator(bool) const {
		return mValue;
	}

	/*
	 * string-value operator
	 */
	public string =operator(string) const {
		return string mValue;
	}

	private bool mValue;
}

public Boolean Boolean(bool value) const {
	return new Boolean(value);
}

