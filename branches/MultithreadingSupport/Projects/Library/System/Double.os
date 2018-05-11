
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Double {
	private double mValue;

	/*
	 * Default constructor
	 */
	public void Constructor(double value val = 0d) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Double value ref) {
		mValue = double value;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(double other val) const {
		return mValue == other;
	}
	public bool operator==(Double other ref) const {
		return mValue == double other;
	}

	public void operator=(double other val) modify {
		mValue = other;
	}
	public void operator=(Double other ref) modify {
		mValue = double other;
	}

	public bool =operator(bool other val) const {
		return bool mValue;
	}
	public double =operator(double other val) const {
		return mValue;
	}

	public void operator+(double other val) modify {
		mValue = mValue + other;
	}
	public void operator+(Double other ref) modify {
		mValue = mValue + double other;
	}

	public void operator-(double other val) modify {
		mValue = mValue - other;
	}
	public void operator-(Double other ref) modify {
		mValue = mValue - double other;
	}

	public void operator*(double other val) modify {
		mValue = mValue * other;
	}
	public void operator*(Double other ref) modify {
		mValue = mValue * double other;
	}

	public void operator/(double other val) modify {
		mValue = mValue / other;
	}
	public void operator/(Double other ref) modify {
		mValue = mValue / double other;
	}
}

public Double Double(double value) const {
	return new Double(value);
}

