
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Boolean {
	private bool mValue;

	public void Constructor(bool value = false) {
		mValue = value;
	}
	public void Constructor(Boolean b) {
		mValue = b.mValue;
	}

	public void FromString(string value) modify {
		print("FromString('" + value + "')");

		if ( value != "" ) {
			mValue = true;
			return;
		}

		mValue = false;
	}

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

/*
	public deprectated bool Value() const {
		return mValue;
	}
	public deprectated void Value(bool value) modify {
		mValue = value;
	}
*/

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(bool other) const {
		return mValue == other;
	}
	public bool operator==(Boolean other) const {
		return mValue == other.mValue;
	}

	public void operator=(bool other) modify {
		mValue = other;
	}
	public void operator=(Boolean other) modify {
		mValue = other.mValue;
	}

	public bool =operator(bool other) const {
		print("bool =operator(bool)");
		return mValue;
	}

	public string =operator(string other) const {
		print("string =operator(string)");
		return string mValue;
	}
}

