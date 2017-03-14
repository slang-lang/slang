
import Exception;
import String;

public namespace System { }

	public object StringIterator {
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
		public void Constructor(StringIterator si) {
			mCurrentPosition = si.mCurrentPosition;
			mSeparator = si.mSeparator;
			mValue = new String(string si);
		}

		/*
		 * hasNext returns true if the iteration did not reach the end of the held String value
		 */
		public bool hasNext() const {
			return mCurrentPosition < mValue.Length();
		}

		/*
		 * next returns the next sub string of the held String value
		 * throws OutOfBoundsException
		 */
		public string next() modify throws {
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
		 * resets the current iteration
		 */
		public void reset() modify {
			mCurrentPosition = 0;
		}

		/*
		 * Change separator token (resets iterator to start)
		 */
		public void setSeparator(string separator) modify {
			mSeparator = separator;

			reset();
		}

		/*
		 * Returns a JSON-like formatted string
		 */
		public string toJsonString() const {
			return "{ " +
					"mCurrentPosition: " + mCurrentPosition + ", " +
					"mSeparator: \"" + mSeparator + "\", " +
					"mValue: " + mValue.ToJsonString() + " " +
				" }";
		}

		/*
		 * Returns a JSON-like formatted string
		 */
		public string toString() const {
			return "StringIterator: { " +
					"mCurrentPosition: " + mCurrentPosition + ", " +
					"mSeparator: \"" + mSeparator + "\", " +
					"mValue: { " + mValue.ToString() + " }" +
				" }";
		}
	}

//}

