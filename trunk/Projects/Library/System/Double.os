
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Double {
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

	/*
	 * Copy operator
	 */
	public Double Copy() const {
		return new Double(mValue);
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(double other val) const {
		return mValue == other;
	}
	public bool operator==(Double other ref) const {
		return mValue == other.mValue;
	}

	public Double operator=(double other val) modify {
		mValue = other;

		return this;
	}
	public Double operator=(Double other ref) modify {
		mValue = other.mValue;

		return this;
	}

	public bool =operator(bool) const {
		return bool mValue;
	}
	public double =operator(double) const {
		return mValue;
	}

	public Double operator+(double other val) modify {
		return new Double(mValue + other);
	}
	public Double operator+(Double other ref) modify {
		return new Double(mValue + other.mValue);
	}

	public Double operator-(double other val) modify {
		return new Double(mValue - other);
	}
	public Double operator-(Double other ref) modify {
		return new Double(mValue - other.mValue);
	}

	public Double operator*(double other val) modify {
		return new Double(mValue * other);
	}
	public Double operator*(Double other ref) modify {
		return new Double(mValue * other.mValue);
	}

	public Double operator/(double other val) modify {
		return new Double(mValue / other);
	}
	public Double operator/(Double other ref) modify {
		return new Double(mValue / other.mValue);
	}

	private double mValue;
}

public Double Double(double value) const {
	return new Double(value);
}

