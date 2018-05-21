
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Integer {
	private int mValue;

	/*
	 * Standard & default constructor
	 */
	public void Constructor(int value val = 0) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Integer i ref) {
		mValue = int i;
	}

	/*
	 * Destructor
	 */
	public void Destructor() {
		// this is empty by intend
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(int other val) const {
		return mValue == other;
	}
	public bool operator==(Integer other const ref) const {
		return mValue == int other;
	}

	public bool operator<(int other) const {
		return mValue < other;
	}
	public bool operator<(Integer other const ref) const {
		return mValue < int other;
	}

	public bool operator>(int other val) const {
		return mValue > other;
	}
	public bool operator>(Integer other const ref) const {
		return mValue > int other;
	}

	/*
	 * int assignment operator
	 */
	public Integer operator=(int other val) modify {
		mValue = other;

		return this;
	}

	/*
	 * Integer assignment operator
	 */
	public Integer operator=(Integer other const ref) modify {
		mValue = int other;

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

	public Integer operator+(int other val) modify {
		mValue = mValue + other;

		return this;
	}
	public Integer operator+(Integer other const ref) modify {
		mValue = mValue + int other;

		return this;
	}

	public Integer operator-(int other val) modify {
		mValue = mValue - other;

		return this;
	}
	public Integer operator-(Integer other const ref) modify {
		mValue = mValue - int other;

		return this;
	}

	public Integer operator*(int other val) modify {
		mValue = mValue * other;

		return this;
	}
	public Integer operator*(Integer other const ref) modify {
		mValue = mValue * int other;

		return this;
	}

	public Integer operator/(int other val) modify {
		mValue = mValue / other;

		return this;
	}
	public Integer operator/(Integer other const ref) modify {
		mValue = mValue / int other;

		return this;
	}
}

public Integer Integer(int value) const {
	return new Integer(value);
}

