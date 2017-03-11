
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Integer {
	private int mValue;

	/*
	 * Standard & default constructor
	 */
	public void Constructor(int value = 0) {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(Integer i ref) {
		mValue = i.mValue;
	}

	/*
	 * Destructor
	 */
	public void Destructor() {
		// this is empty by intend
	}

	/*
	 * Returns a JSON-formatted string
	 */
	public deprecated string ToJsonString() const {
		return "{ "
		     + "mValue: " + mValue
		     + " }";
	}

	public deprecated string ToString() const {
		return "Integer: " +  mValue;
	}

	public bool operator!() const {
		return !mValue;
	}

	public bool operator==(int other) const {
		return mValue == other;
	}
	public bool operator==(Integer other ref) const {
		return mValue == other;
	}

	public bool operator<(int other) const {
		return mValue < other;
	}
	public bool operator<(Integer other ref) const {
		return mValue < other;
	}

	public bool operator>(int other) const {
		return mValue > other;
	}
	public bool operator>(Integer other ref) const {
		return mValue > other;
	}

	/*
	 * int assignment operator
	 */
	public void operator=(int other) modify {
		mValue = other;
	}

	/*
	 * Integer assignment operator
	 */
	public void operator=(Integer other ref) modify {
		mValue = other;
	}

	/*
	 * int value operator
	 */
	public int =operator(int other) const {
		return mValue;
	}

	/*
	 * string value operator
	 */
	public string =operator(string none) const {
		return string mValue;
	}

	public void operator+(int other) modify {
		mValue = mValue + other;
	}
	public void operator+(Integer other ref) modify {
		mValue = mValue + int other;
	}

	public void operator-(int other) modify {
		mValue = mValue - other;
	}
	public void operator-(Integer other ref) modify {
		mValue = mValue - int other;
	}

	public void operator*(int other) modify {
		mValue = mValue * other;
	}
	public void operator*(Integer other ref) modify {
		mValue = mValue * int other;
	}

	public void operator/(int other) modify {
		mValue = mValue / other;
	}
	public void operator/(Integer other ref) modify {
		mValue = mValue / int other;
	}
}

