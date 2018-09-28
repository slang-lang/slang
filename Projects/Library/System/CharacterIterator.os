
import Collections.Iterator;
import String;

// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public object CharacterIterator extends Iterator<string> {
	/*
	 * Standard string constructor
	 */
	public void Constructor(string value = "") {
		reset(value);
	}

	/*
	 * Standard String constructor
	 */
	public void Constructor(String value const) {
		reset(string value);
	}

	/*
	 * returns the value of the current iteration
	 * throws NotInitializedException
	 * throws OutOfBoundsException
	 */
	public string current() const throws {
		if ( mCurrentIndex < 0 ) {
			throw new NotInitializedException("iterator not initialized");
		}
		if ( mCurrentIndex > mLength) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + ") out of bounds");
		}

		return substr(mValue, mCurrentIndex, 1);
	}

	/*
	 * returns true if the iteration did not reach the end of the held string value
	 */
	public bool hasNext() const {
		return mCurrentIndex < mLength;
	}

	/*
	 * returns the next character of the held string value, without changing the current iteration index
	 * throws OutOfBoundsException
	 */
	public string lookAHead(int offset = 1) const throws {
		if ( mCurrentIndex + offset < 0 || mCurrentIndex + offset > mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + offset + ") out of bounds");
		}

		return substr(mValue, mCurrentIndex + offset, 1);
	}

	/*
	 * returns the next character of the held string value
	 * throws OutOfBoundsException
	 */
	public string next() modify throws {
		if ( mCurrentIndex + 1 > mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + 1 + ") out of bounds");
		}

		mCurrentIndex++;
		return substr(mValue, mCurrentIndex, 1);
	}

	/*
	 * resets the current iteration
	 */
	public void reset(string value = "") modify {
		mCurrentIndex = -1;
		mLength = strlen(value);
		mValue = value;
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
	 * returns the next character of the held string value
	 * equivalent to calling next()
	 * throws OutOfBoundsException
	 */
	public string operator++() modify throws {
		return next();
	}

	private int mCurrentIndex;
	private int mLength;
	private string mValue;
}

