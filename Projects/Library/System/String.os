
public namespace System {

	public object String {
		private string mValue;

		/*
		 * Standard & default constructor
		 */
		public void String(string value = "") {
			mValue = value;
		}

		/*
		 * Copy constructor
		 */
		public void String(String copy) {
			mValue = copy.mValue;
		}

		/*
		 * Returns the character at the given position
		 */
		public string At(int index) const {
			return substr(mValue, index, 1);
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
		 * Returns the start position of the given string
		 */
/*
		public int Find(string str, int startpos) const {
			string val = substr(mValue, startpos);

			return strfind(val, str);
		}
*/
		/*
		 * Returns the length of the held string
		 */
		public int Length() const {
			return strlen(mValue);
		}

		/*
		 * Replaces the first occurance of the given string with the provided new string
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
		 * Replaces all occurances of a given string with a new string
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
		 * Returns the held string as it is
		 */
		public string ToString() const {
			return "String: \"" + mValue + "\"";
		}

		/*
		 * Returns the held string in capital letters
		 */
		public string ToUpperCase() const {
			return toUpper(mValue);
		}

		/*
		 * Deprecated: use (active) value operator instead
		 * returns String.mValue as string
		 */
		public deprecated string Value() const {
			return mValue;
		}

		/*
		 * Deprecated: use (passive) assignment operator instead
		 * sets String.mValue from a string
		 */
		public deprecated void Value(string value) modify {
			mValue = value;
		}

		public string =operator(string value) const {
			return mValue;
		}

		public bool operator!() const {
			return !mValue;
		}

		public bool operator==(string other) const {
			return (mValue == other);
		}
		public bool operator==(String other) const {
			return (mValue == other.mValue);
		}

		public void operator=(string other) modify {
			mValue = other;
		}
		public void operator=(String other) modify {
			mValue = other.mValue;
		}

		public void operator+(string other) modify {
			mValue = mValue + other;
		}
		public void operator+(String other) modify {
			mValue = mValue + other.mValue;
		}
	}

}

