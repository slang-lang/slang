
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Boolean {
	private bool mValue;

	/*
	 * Default constructor 
	 */
	public void Constructor(bool value val = false) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Boolean value ref) {
		mValue = bool value;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(bool other val) const {
		return mValue == other;
	}
	public bool operator==(Boolean other ref) const {
		return mValue == bool other;
	}

	public void operator=(bool other val) modify {
		mValue = other;
	}
	public void operator=(Boolean other ref) modify {
		mValue = bool other;
	}

	/*
	 * bool-value operator
	 */
	public bool =operator(bool none val) const {
		return mValue;
	}

	/*
	 * string-value operator
	 */
	public string =operator(string none val) const {
		return string mValue;
	}
}

public Boolean Boolean(bool value) const {
	return new Boolean(value);
}

