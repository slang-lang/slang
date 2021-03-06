
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Float {
	/*
	 * Default constructor
	 */
	public void Constructor(float value = 0f) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Float value const) {
		mValue = float value;
	}

	/*
	 * Copy operator
	 */
	public Float Copy() const {
		return new Float(mValue);
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(float other) const {
		return mValue == other;
	}
	public bool operator==(Float other const) const {
		return mValue == other.mValue;
	}

	public Float operator=(float other) modify {
		mValue = other;

		return this;
	}
	public Float operator=(Float other const) modify {
		mValue = other.mValue;

		return this;
	}

	public bool =operator(bool) const {
		return bool mValue;
	}
	public float =operator(float) const {
		return mValue;
	}

	public Float operator+(float other) const {
		return new Float(mValue + other);
	}
	public Float operator+(Float other const) const {
		return new Float(mValue + other.mValue);
	}

	public Float operator-(float other) const {
		return new Float(mValue - other);
	}
	public Float operator-(Float other const) const {
		return new Float(mValue - other.mValue);
	}

	public Float operator*(float other) const {
		return new Float(mValue * other);
	}
	public Float operator*(Float other const) const {
		return new Float(mValue * other.mValue);
	}

	public Float operator/(float other) const {
		return new Float(mValue / other);
	}
	public Float operator/(Float other const) const {
		return new Float(mValue / other.mValue);
	}

	private float mValue;
}

public Float Float(float value) const {
	return new Float(value);
}

