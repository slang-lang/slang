
import Exception;
import String;

public namespace System { }

public object StringIterator {
	private int mCurrentPosition;
	private int mNextPosition;
	private string mSeparator;
	private String mValue;

	/*
	 * Standard constructor
	 */
	public void Constructor(String value, string separator = " ") {
		mSeparator = separator;
		mValue = value;

		reset();
	}

	/*
	 * Secondary constructor
	 */
	public void Constructor(string value, string separator = " ") {
		mSeparator = separator;
		mValue = new String(value);

		reset();
	}

	/*
	 * returns the value of the current iteration
	 * throws Exception
	 * throws OutOfBoundsException
	 */
	public string current() const throws {
		if ( mCurrentPosition == -1 ) {
			throw new Exception("iterator not initialized");
		}
		if ( mCurrentPosition >= mNextPosition ) {
			throw new OutOfBoundsException("out of bounds");
		}

		return mValue.SubString(mCurrentPosition, mNextPosition - mCurrentPosition);
	}

	/*
	 * returns true if the iteration did not reach the end of the held String value
	 */
	public bool hasNext() const {
		return mNextPosition < mValue.Length();
	}

	/*
	 * returns the next sub string of the held String value
	 * throws OutOfBoundsException
	 */
	public string next() modify throws {
		if ( mNextPosition >= mValue.Length() ) {
			throw new OutOfBoundsException("out of bounds");
		}

		mCurrentPosition = mNextPosition + strlen(mSeparator);
		mNextPosition = mValue.Find(mSeparator, mCurrentPosition);

		if ( mNextPosition > 0 ) {
			return mValue.SubString(mCurrentPosition, mNextPosition - mCurrentPosition);
		}

		// set iteration to end of string
		mNextPosition = mValue.Length();
		return mValue.SubString(mCurrentPosition);
	}

	/*
	 * resets the current iteration
	 */
	public void reset() modify {
		mCurrentPosition = -1;
		mNextPosition = strlen(mSeparator) * -1;
	}

	/*
	 * changes the separator token (optionally resets iterator to start)
	 */
	public void setSeparator(string separator, bool doReset = true) modify {
		mSeparator = separator;

		if ( doReset ) {
			reset();
		}
	}

	/*
	 * returns the value of the current iteration
	 * throws OutOfBoundsException
	 */
	public string =operator(string none) const throws {
		return current();
	}

	/*
	 * increments the iteration step
	 * throws OutOfBoundsException
	 */
	public void operator++() modify throws {
		next();
	}
}

