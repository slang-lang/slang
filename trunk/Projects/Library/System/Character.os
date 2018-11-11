
import Exception;

// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object Character {
	/*
	 * Standard & default constructor
	 */
	public void Constructor(string value val = "", bool checkLength = false) throws {
		if ( checkLength && strlen(value) != 1) {
			throw new InvalidLengthException("invalid input length(" + strlen(value) + ")");
		}

		// a character can only have a value of string(length: 1)
		mValue = substr(value, 0, 1);
	}

	/*
	 * Copy operator
	 */
	public Character Copy() const {
		return new Character(mValue);
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
		return operator==(other.mValue);
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
		operator=(other.mValue);
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
		return operator<(other.mValue);
	}

	/*
	 * int typecast operator
	 */
	public int =operator(int) const {
		return int mValue;
	}

	/*
	 * string typecast operator
	 */
	public string =operator(string) const {
		return mValue;
	}

	private string mValue;
}

public Character Character(string value) const {
	return new Character(value);
}

