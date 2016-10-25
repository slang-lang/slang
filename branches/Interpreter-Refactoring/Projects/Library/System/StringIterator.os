
import Exception;
import String;

public namespace System {

	public object StringIterator /*implements IIterateable*/ {
		private int mCurrentPosition;
		private string mSeparator;
		private String mValue;

		/*
		 * Standard constructor
		 */
		public void Constructor(string value, string separator = " ") {
			mCurrentPosition = 0;
			mSeparator = separator;
			mValue = new String(value);
		}

		/*
		 * Copy constructor
		 */
		public void Constructor(System.StringIterator si) {
			mCurrentPosition = si.mCurrentPosition;
			mSeparator = si.mSeparator;
			mValue = new String(si.mValue);
		}

		/*
		 * HasNext returns true if the iteration did not reach the end of the held String value
		 */
		public bool HasNext() const {
			return mCurrentPosition < mValue.Length();
		}

		/*
		 * GetNext returns the next sub string of the held String value
		 * throws OutOfBoundsException
		 */
		public string GetNext() modify throws {
			if ( mCurrentPosition >= mValue.Length() ) {
				throw new OutOfBoundsException("out of bounds");
			}

			int oldPos = mCurrentPosition;
			int newPos = mValue.Find(mSeparator, oldPos);

			if ( newPos > 0 ) {
				mCurrentPosition = newPos + strlen(mSeparator);
				return mValue.SubString(oldPos, newPos - oldPos);
			}

			mCurrentPosition = mValue.Length();
			return mValue.SubString(oldPos);
		}

		/*
		 * Resets the current iteration
		 */
		public void Reset() modify {
			mCurrentPosition = 0;
		}

		/*
		 * Change separator token (resets iterator to start)
		 */
		public void SetSeparator(string separator) modify {
			mSeparator = separator;

			Reset();
		}

		/*
		 * Returns a JSON-like formatted string
		 */
		public string ToJsonString() const {
			return "{ " +
					"mCurrentPosition: " + mCurrentPosition + ", " +
					"mSeparator: \"" + mSeparator + "\", " +
					"mValue: " + mValue.ToJsonString() + " " +
				" }";
		}

		/*
		 * Returns a JSON-like formatted string
		 */
		public string ToString() const {
			return "StringIterator: { " +
					"mCurrentPosition: " + mCurrentPosition + ", " +
					"mSeparator: \"" + mSeparator + "\", " +
					"mValue: { " + mValue.ToString() + " }" +
				" }";
		}
	}

}

