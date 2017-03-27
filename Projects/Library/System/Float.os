
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Float {
	private float mValue;

	public void Constructor(float value = 0f) {
		mValue = value;
	}
	public void Constructor(Float f ref) {
		mValue = f.mValue;
	}

/*
	public void FromString(string value) modify {
		mValue = float value;
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
		return "Float: " + mValue;
	}

/*
	public deprecated float Value() const {
		return mValue;
	}
	public deprecated void Value(float value) modify {
		mValue = value;
	}
*/

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(float other) const {
		return mValue == other;
	}
	public bool operator==(Float other ref) const {
		return mValue == other;
	}

	public void operator=(float other) modify {
		mValue = other;
	}
	public void operator=(Float other ref) modify {
		mValue = other;
	}

	public float =operator(float other) const {
		return mValue;
	}

	public void operator+(float other) modify {
		mValue = mValue + other;
	}
	public void operator+(Float other ref) modify {
		mValue = mValue + float other;
	}

	public void operator-(float other) modify {
		mValue = mValue - other;
	}
	public void operator-(Float other ref) modify {
		mValue = mValue - float other;
	}

	public void operator*(float other) modify {
		mValue = mValue * other;
	}
	public void operator*(Float other ref) modify {
		mValue = mValue * float other;
	}

	public void operator/(float other) modify {
		mValue = mValue / other;
	}
	public void operator/(Float other ref) modify {
		mValue = mValue / float other;
	}
}

