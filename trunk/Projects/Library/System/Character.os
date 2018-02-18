
import Exception;

// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Character {
    private string mValue;

	/*
	 * Standard & default constructor
	 */
	public void Constructor(string value val = "", bool checkLength = false) throws {
		if ( checkLength && strlen(value) != 1) {
			throw new Exception("invalid input length(" + strlen(value) + ")");
		}

        // a character can only have a value of string(length: 1)
		mValue = substr(value, 0, 1);
	}

	/*
	 * Validation operator
	 */
	public bool operator!() const {
		return !mValue;
	}

	/*
	 * string compare operator
	 */
	public bool operator==(string other val) const {
		return mValue == substr(other, 0, 1);
	}

	/*
	 * Character compare operator
	 */
	public bool operator==(Character other ref) const {
		return mValue == string other;
	}

	/*
	 * string assignment operator
	 */
	public void operator=(string other val) modify {
		mValue = substr(other, 0, 1);
	}

	/*
	 * Character assignment operator
	 */
	public void operator=(Character other ref) modify {
		mValue = string other;
	}

	/*
	 * string less compare operator
	 */
	public bool operator<(string other val) const {
		return mValue < substr(other, 0, 1);
	}

	/*
	 * Character less compare operator
	 */
	public bool operator<(Character other ref) const {
		return mValue < string other;
	}

	/*
	 * int typecast operator
	 */
	public int =operator(int none) const {
		return int mValue;
	}

	/*
	 * string typecast operator
	 */
	public string =operator(string none) const {
		return mValue;
	}
}

public Character Character(string value) const {
	return new Character(value);
}

