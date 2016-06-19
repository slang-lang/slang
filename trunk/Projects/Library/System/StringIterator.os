
import System.Exception;
import System.String;

public namespace System {

	public object StringIterator {
		private int mCurrentPosition;
		private string mSeparator;
		private String mValue;

		/*
		 * Standard constructor
		 */
		public void StringIterator(string value, string separator = " ") {
			mCurrentPosition = 0;
			mSeparator = separator;
			mValue = new String(value);
		}

		/*
		 * Copy constructor
		 */
		public void StringIterator(StringIterator copy) {
			mCurrentPosition = copy.mCurrentPosition;
			mSeparator = copy.mSeparator;
			mValue = new String(copy.mValue);
		}

		/*
		 * Change separator token (resets iterator to start)
		 */
		public void setSeparator(string separator) modify {
			mCurrentPosition = 0;
			mSeparator = separator;
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
		public string GetNext() modify {
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

		public string ToString() const {
			return "StringIterator: { " +
					"mCurrentPosition: " + mCurrentPosition + ", " +
					"mSeparator: \"" + mSeparator + "\", " +
					"mValue: { " + mValue.ToString() + " }" +
				" }";
		}
	}

}

