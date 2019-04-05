
import CharacterIterator;
import Collections.IIterateable;
import Exception;
import StringIterator;

// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object String implements IIterateable {
	/*
	 * Standard & default constructor
	 */
	public void Constructor(string value = "") {
		mValue = value;
		mSize = strlen(mValue);
	}

	/*
	 * double cast constructor
	 */
	public void Constructor(double value) {
		mValue = string value;
		mSize = strlen(mValue);
	}

	/*
	 * float cast constructor
	 */
	public void Constructor(float value) {
		mValue = string value;
		mSize = strlen(mValue);
	}

	/*
	 * int cast constructor
	 */
	public void Constructor(int value) {
		mValue = string value;
		mSize = strlen(mValue);
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(String value) {
		Constructor(string value);
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
	public String Copy() {
		return new String(mValue);
	}

	/*
	 * Returns the character at the given position
	 */
	public string CharAt(int index) const throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException("index(" + index + ") is out of bounds!");
		}

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
	 * Returns an iterator that iterates over all characters of the held string
	 */
	public CharacterIterator getIterator() const {
		return new CharacterIterator(this);
	}

	/*
	 * Returns the start position of the given string
	 */
	public int IndexOf(string str, int startpos = 0) const {
		return strfind(mValue, str, startpos);
	}

	/*
	 * Returns the index of the last occurence of the given string
	 */
	public int LastIndexOf(string str) const {
		int index = -1;
		int index2;

		while ( (index2 = IndexOf(str, index + 1)) != -1 ) {
			index = index2;
		}

		return index;
	}

	/*
	 * Returns the length of the held string
	 */
	public int Length() const {
		return mSize;
	}

	/*
	 * Replaces the first occurrence of the given string with the provided new string
	 */
	public bool Replace(string oldStr, string newStr) modify {
		int position = strfind(mValue, oldStr, 0);

		if ( position > 0 ) {
			string tmp = substr(mValue, 0, position) + newStr + substr(mValue, position + strlen(oldStr));

			// update members
			mValue = tmp;
			mSize = strlen(mValue);

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

		// update size
		//mSize = strlen(mValue);	// this should already be updated

		return hasFound;
	}

	/*
	 * Removes the character at the given position
	 */
	public void RemoveCharAt(int index) modify throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException("index(" + index + ") is out of bounds!");
		}

		mSize--;
		mValue = substr(mValue, 0, index) + substr(mValue, index + 1);
	}

	/*
	 * Splits the held string into substrings using a single whitespace as separator
	 */
	public StringIterator Split() const {
		return new StringIterator(this, " ");
	}

	/*
	 * Splits the held string into substrings using the given separator
	 */
	public StringIterator SplitBy(string separator) const {
		return new StringIterator(this, separator);
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
	public String ToLower() const {
		return new String(toLower(mValue));
	}

	/*
	 * Returns the held string in lower case letters
	 */
	public string ToLowerCase() const {
		return toLower(mValue);
	}

	/*
	 * Trims whitespaces from the left side of the held string value
	 */
	public string TrimLeft() modify {
		mValue = strltrim(mValue);
		mSize = strlen(mValue);

		return mValue;
	}

	/*
	 * Cuts away from the left side of the held string value
	 */
	public string TrimLeft(int index) modify throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException("index(" + index + ") is out of bounds!");
		}

		mValue = substr(mValue, index);
		mSize = strlen(mValue);

		return mValue;
	}

	/*
	 * Trims whitespaces from the right side of the held string value
	 */
	public string TrimRight() modify {
		mValue = strrtrim(mValue);
		mSize = strlen(mValue);

		return mValue;
	}

	/*
	 * Cuts away from the right side of the held string value
	 */
	public string TrimRight(int index) modify {
		mValue = substr(mValue, 0, strlen(mValue) - index);
		mSize = strlen(mValue);

		return mValue;
	}

	/*
	 * Trims whitespaces from both sides of the held string value
	 */
	public string Trim() modify {
		mValue = strltrim(mValue);
		mValue = strrtrim(mValue);

		return mValue;
	}

	/*
	 * Returns the held string in capital letters
	 */
	public string ToUpperCase() const {
		return toUpper(mValue);
	}

	/*
	 * string typecast operator
	 */
	public string =operator(string) const {
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
	public bool operator==(string other) const {
		return mValue == other;
	}

	/*
	 * String compare operator
	 */
	public bool operator==(String other const) const {
		return mValue == other.mValue;
	}

	/*
	 * string assignment operator
	 */
	public String operator=(string other) modify {
		// update members
		mValue = other;
		mSize = strlen(mValue);

		return this;
	}

	/*
	 * String assignment operator
	 */
	public String operator=(String other const) modify {
		return operator=(string other);
	}

	/*
	 * string concatenation operator
	 */
	public String operator+(string other) const {
		return new String(mValue + other);
	}

	/*
	 * String concatenation operator
	 */
	public String operator+(String other const) const {
		return new String(mValue + other.mValue);
	}

	/*
	 * string less compare operator
	 */
	public bool operator<(string other) const {
		return mValue < other;
	}

	/*
	 * String less compare operator
	 */
	public bool operator<(String other const) const {
		return mValue < other.mValue;
	}

	/*
	 * Returns the character at the given position
	 */
	public string operator[](int index) const throws {
		return CharAt(index);
	}

	private int mSize;
	private string mValue;
}

/*
 * String cast constructor
 */
public String String(string value) const {
	return new String(value);
}

