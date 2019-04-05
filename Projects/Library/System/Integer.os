
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Integer {
	/*
	 * Standard & default constructor
	 */
	public void Constructor(int value = 0) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Integer i const) {
		mValue = int i;
	}

	/*
	 * Destructor
	 */
	public void Destructor() {
		// this is empty by intend
	}

	/*
	 * Copy operator
	 */
	public Integer Copy() const {
		return new Integer(mValue);
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(int other) const {
		return mValue == other;
	}
	public bool operator==(Integer other const) const {
		return mValue == other.mValue;
	}

	public bool operator<(int other) const {
		return mValue < other;
	}
	public bool operator<(Integer other const) const {
		return mValue < other.mValue;
	}

	public bool operator>(int other) const {
		return mValue > other;
	}
	public bool operator>(Integer other const) const {
		return mValue > other.mValue;
	}

	/*
	 * int assignment operator
	 */
	public Integer operator=(int other) modify {
		mValue = other;

		return this;
	}

	/*
	 * Integer assignment operator
	 */
	public Integer operator=(Integer other const) modify {
		mValue = other.mValue;

		return this;
	}

	/*
	 * int typecast operator
	 */
	public int =operator(int) const {
		return mValue;
	}

	/*
	 * string typecast operator
	 */
	public string =operator(string) const {
		return string mValue;
	}

	public Integer operator+(int other) const {
		return new Integer(mValue + other);
	}
	public Integer operator+(Integer other const) const {
		return new Integer(mValue + other.mValue);
	}

	public Integer operator-(int other) const {
		return new Integer(mValue - other);
	}
	public Integer operator-(Integer other const) const {
		return new Integer(mValue - other.mValue);
	}

	public Integer operator*(int other) const {
		return new Integer(mValue * other);
	}
	public Integer operator*(Integer other const) const {
		return new Integer(mValue * other.mValue);
	}

	public Integer operator/(int other) const {
		return new Integer(mValue / other);
	}
	public Integer operator/(Integer other const) const {
		return new Integer(mValue / other.mValue);
	}

	private int mValue;
}

public Integer Integer(int value) const {
	return new Integer(value);
}

