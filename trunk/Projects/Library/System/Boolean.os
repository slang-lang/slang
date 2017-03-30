
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Boolean {
	private bool mValue;

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
		mValue = bool value;
	}

/*
	public void FromString(string value) modify {
		print("FromString('" + value + "')");

		if ( value != "" ) {
			mValue = true;
			return;
		}

		mValue = false;
	}
*/

	/*
	 * Returns a JSON-formatted string
	 */
	public string ToJsonString() const {
		return "{ "
		     + "mValue: " + mValue
		     + " }";
	}

	public string ToString() const {
		return "Boolean: " + mValue;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(bool other) const {
		return mValue == other;
	}
	public bool operator==(Boolean other ref) const {
		return mValue == other;
	}

	public void operator=(bool other) modify {
		mValue = other;
	}
	public void operator=(Boolean other ref) modify {
		mValue = other;
	}

	/*
	 * bool-value operator
	 */
	public bool =operator(bool other) const {
		return mValue;
	}

	/*
	 * string-value operator
	 */
	public string =operator(string other) const {
		return string mValue;
	}
}

