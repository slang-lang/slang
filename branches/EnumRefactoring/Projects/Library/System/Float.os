
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Float {
	private float mValue;

	/*
	 * Default constructor
	 */
	public void Constructor(float value val = 0f) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Float value ref) {
		mValue = float value;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(float other val) const {
		return mValue == other;
	}
	public bool operator==(Float other ref) const {
		return mValue == float other;
	}

	public void operator=(float other val) modify {
		mValue = other;
	}
	public void operator=(Float other ref) modify {
		mValue = float other;
	}

	public float =operator(float other val) const {
		return mValue;
	}

	public void operator+(float other) modify {
		mValue = mValue + other;
	}
	public void operator+(Float other ref) modify {
		mValue = mValue + float other;
	}

	public void operator-(float other val) modify {
		mValue = mValue - other;
	}
	public void operator-(Float other ref) modify {
		mValue = mValue - float other;
	}

	public void operator*(float other val) modify {
		mValue = mValue * other;
	}
	public void operator*(Float other ref) modify {
		mValue = mValue * float other;
	}

	public void operator/(float other val) modify {
		mValue = mValue / other;
	}
	public void operator/(Float other ref) modify {
		mValue = mValue / float other;
	}
}

public Float Float(float value) const {
	return new Float(value);
}

