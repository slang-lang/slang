
import Collections.IIterateable;
import StringIterator;

// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object String implements IIterateable {
	private string mValue;

	/*
	 * Standard & default constructor
	 */
	public void Constructor(string value val = "") {
		mValue = value;
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(String s ref) {
		mValue = string s;
	}

	/*
	 * Returns the character at the given position
	 */
	public string At(int index) const {
		return substr(mValue, index, 1);
	}

	/*
	 * Returns true if the given string is part of the held string
	 */
	public bool Contains(string value) const {
		return strfind(mValue, value, 0) >= 0;
	}

	/*
	 * Returns true if the held string ends with the given string
	 */
	public bool EndsWith(string str) const {
		return str == substr(mValue, strlen(mValue) - strlen(str));
	}

	/*
	 * Returns the start position of the given string
	 */
	public int Find(string str, int startpos = 0) const {
		return strfind(mValue, str, startpos);
	}

	/*
	 * Returns an Iterator that is attached to this string
	 */
	public StringIterator getIterator(string separator = " ") const {
		return new StringIterator(this, separator);
	}

	/*
	 * Returns the length of the held string
	 */
	public int Length() const {
		return strlen(mValue);
	}

	/*
	 * Replaces the first occurrence of the given string with the provided new string
	 */
	public bool Replace(string oldStr, string newStr) modify {
		int position = strfind(mValue, oldStr, 0);

		if ( position > 0 ) {
			string tmp = substr(mValue, 0, position) + newStr + substr(mValue, position + strlen(oldStr));
			mValue = tmp;
			return true;
		}
		
		return false;
	}

	/*
	 * Replaces all occurrences of a given string with a new string
	 */
	public bool ReplaceAll(string oldStr, string newStr) modify {
		bool hasFound = false;

		while ( Replace(oldStr, newStr) ) {
			hasFound = true;
		}

		return hasFound;
	}

	/*
	 * Returns true if the held string starts with the given string
	 */
	public bool StartsWith(string str) const {
		return str == substr(mValue, 0, strlen(str));
	}

	/*
	 * Returns all characters beginning with start until the end of the held string
	 */
	public string SubString(int start) const {
		return substr(mValue, start);
	}

	/*
	 * Returns all characters of the held string between the given start and end position
	 */
	public string SubString(int start, int length) const {
		return substr(mValue, start, length);
	}

	/*
	 * Returns the held string in lower case letters
	 */
	public string ToLowerCase() const {
		return toLower(mValue);
	}

	/*
	 * Returns the held string in capital letters
	 */
	public string ToUpperCase() const {
		return toUpper(mValue);
	}

	/*
	 * String value operator
	 */
	public string =operator(string value) const {
		return mValue;
	}

	/*
	 * String validation operator
	 */
	public bool operator!() const {
		return !mValue;
	}

	/*
	 * string compare operator
	 */
	public bool operator==(string other val) const {
		return (mValue == other);
	}
	/*
	 * String compare operator
	 */
	public bool operator==(String other ref) const {
		return mValue == string other;
	}

	/*
	 * string assignment operator
	 */
	public void operator=(string other val) modify {
		mValue = other;
	}
	/*
	 * String assignment operator
	 */
	public void operator=(String other ref) modify {
		mValue = string other;
	}

	/*
	 * string concatenation operator
	 */
	public void operator+(string other val) modify {
		mValue = mValue + other;
	}
	/*
	 * String concatenation operator
	 */
	public void operator+(String other ref) modify {
		mValue = mValue + string other;
	}

	/*
	 * string less compare operator
	 */
	public bool operator<(string other val) const {
		return mValue < other;
	}

	/*
	 * String less compare operator
	 */
	public bool operator<(String other ref) const {
		return mValue < string other;
	}

	/*
	 * String subscript operator
	 */
	public string operator[](int index) const {
		return substr(mValue, index, 1);
	}
}

