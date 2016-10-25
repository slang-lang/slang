
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Double {
	private double mValue;

	public void Constructor(double value = 0d) {
		mValue = value;
	}
	public void Constructor(Double d) {
		mValue = d.mValue;
	}

	public void FromString(string value) modify {
		mValue = double value;
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
		return "Double: " + mValue;
	}

	public deprecated double Value() const {
		return mValue;
	}
	public deprecated void Value(double value) modify {
		mValue = value;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(double other) const {
		return mValue == other;
	}
	public bool operator==(Double other) const {
		return mValue == other.mValue;
	}

	public void operator=(double other) modify {
		mValue = other;
	}
	public void operator=(Double other) modify {
		mValue = other.mValue;
	}

	public bool =operator(bool other) const {
		return mValue;
	}
	public double =operator(double other) const {
		return mValue;
	}

	public void operator+(double other) modify {
		mValue = mValue + other;
	}
	public void operator+(Double other) modify {
		mValue = mValue + other.mValue;
	}

	public void operator-(double other) modify {
		mValue = mValue - other;
	}
	public void operator-(Double other) modify {
		mValue = mValue - other.mValue;
	}

	public void operator*(double other) modify {
		mValue = mValue * other;
	}
	public void operator*(Double other) modify {
		mValue = mValue * other.mValue;
	}

	public void operator/(double other) modify {
		mValue = mValue / other;
	}
	public void operator/(Double other) modify {
		mValue = mValue / other.mValue;
	}
}

