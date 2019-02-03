
import Collections.Iterator;
import Exception;
import String;

// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object StringIterator extends Iterator<string> {
	/*
	 * Standard constructor
	 */
	public void Constructor(string value, string separator = " ") {
		mValue = new String(value);

		setSeparator(separator, true);
	}

	/*
	 * Copy constructor
	 */
	public void Constructor(String value const, string separator = " ") {
		mValue = value;

		setSeparator(separator, true);
	}

	/*
	 * Copy operator
	 */
	public StringIterator Copy() const {
		return new StringIterator(mValue, mSeparator);
	}

	/*
	 * returns the value of the current iteration
	 * throws NotInitializedException
	 * throws OutOfBoundsException
	 */
	public string current() const throws {
		if ( mCurrentPosition < 0 ) {
			throw new NotInitializedException("iterator not initialized");
		}
		if ( mNextPosition > mValue.Length() ) {
			throw new OutOfBoundsException("index(" + mNextPosition + ") out of bounds");
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
			throw new OutOfBoundsException("index(" + mNextPosition + ") out of bounds");
		}

		mCurrentPosition = mNextPosition + strlen(mSeparator);
		mNextPosition = mValue.IndexOf(mSeparator, mCurrentPosition);

		if ( mNextPosition > 0 ) {
			return mValue.SubString(mCurrentPosition, mNextPosition - mCurrentPosition);
		}

		// set iteration to end of string
		mNextPosition = mValue.Length();
		return mValue.SubString(mCurrentPosition);
	}

	/*
	 * temporarly changes the separator and returns the next sub string of the held String value
	 * throws OutOfBoundsException
	 */
	public string next(string separator) modify throws {
		if ( mNextPosition >= mValue.Length() ) {
			throw new OutOfBoundsException("index(" + mNextPosition + ") out of bounds");
		}

		mCurrentPosition = mNextPosition + strlen(mSeparator);
		mNextPosition = mValue.IndexOf(separator, mCurrentPosition);

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
	public void setSeparator(string separator, bool doReset = false) modify {
		mSeparator = separator;

		if ( doReset ) {
			reset();
		}
		else {
			mNextPosition = mValue.IndexOf(mSeparator, mCurrentPosition);

			if ( mNextPosition <= 0 ) {
				mNextPosition = mValue.Length();
			}
		}
	}

	/*
	 * returns the value of the current iteration
	 * equivalent to calling current()
	 * throws NotInitializedException, OutOfBoundsException
	 */
	public string =operator(string) const throws {
		return current();
	}

	/*
	 * Equality operator
	 */
	public bool operator==(StringIterator other const) const {
		return mValue == other.mValue && mCurrentPosition == other.mCurrentPosition;
	}

	/*
	 * returns the next sub string of the held String value
	 * equivalent to calling next()
	 * throws OutOfBoundsException
	 */
	public string operator++() modify throws {
		return next();
	}

	private int mCurrentPosition;
	private int mNextPosition;
	private string mSeparator;
	private String mValue const;
}

