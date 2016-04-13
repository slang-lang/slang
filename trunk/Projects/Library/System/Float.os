
public object Float
{
	private float mValue;

	public void Float(float value = 0.f) {
		mValue = value;
	}

	public void FromString(string value) {
		mValue = (float value);
	}

	public string ToString() const {
		return (string mValue);
	}

	public float Value() const {
		return mValue;
	}
	public void Value(float value) modify {
		mValue = value;
	}

	public bool operator==(float other) const {
		return (mValue == other);
	}
	public bool operator==(Float other) const {
		return (mValue == other.mValue);
	}

	public void operator=(float other) modify {
		mValue = other;
	}
	public void operator=(Float other) modify {
		mValue = other.mValue;
	}

	public void operator+(float other) modify {
		mValue = mValue + other;
	}
	public void operator+(Float other) modify {
		mValue = other.mValue;
	}

	public void operator-(float other) modify {
		mValue = mValue - other;
	}
	public void operator-(Float other) modify {
		mValue = mValue - other.mValue;
	}

	public void operator*(float other) modify {
		mValue = mValue * other;
	}
	public void operator*(Float other) modify {
		mValue = mValue * other.mValue;
	}

	public void operator/(float other) modify {
		mValue = mValue / other;
	}
	public void operator/(Float other) modify {
		mValue = mValue / other.mValue;
	}
}

