
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Double {
	private double mValue;

	/*
	 * Default constructor
	 */
	public void Constructor(double value = 0d) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Double value ref) {
		mValue = double value;
	}

/*
	public void FromString(string value) modify {
		mValue = double value;
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
	public bool operator==(Double other ref) const {
		return mValue == double other;
	}

	public void operator=(double other) modify {
		mValue = other;
	}
	public void operator=(Double other ref) modify {
		mValue = double other;
	}

	public bool =operator(bool other) const {
		return bool mValue;
	}
	public double =operator(double other) const {
		return mValue;
	}

	public void operator+(double other) modify {
		mValue = mValue + other;
	}
	public void operator+(Double other ref) modify {
		mValue = mValue + double other;
	}

	public void operator-(double other) modify {
		mValue = mValue - other;
	}
	public void operator-(Double other ref) modify {
		mValue = mValue - double other;
	}

	public void operator*(double other) modify {
		mValue = mValue * other;
	}
	public void operator*(Double other ref) modify {
		mValue = mValue * double other;
	}

	public void operator/(double other) modify {
		mValue = mValue / other;
	}
	public void operator/(Double other ref) modify {
		mValue = mValue / double other;
	}
}
