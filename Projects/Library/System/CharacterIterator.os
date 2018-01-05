
import System.Collections.Iterator;

public object CharacterIterator implements Iterator {
	private int mCurrentPos;
	private int mLength;
	private string mValue;

	public void Constructor(string value = "") {
		reset(value);
	}

	public string current() const throws {
		if ( !mValue ) {
			throw new Exception("invalid iteration string");
		}

		return substr(mValue, mCurrentPos, 1);
	}

	public bool hasNext() const {
		return mCurrentPos < mLength;
	}

	public void next() modify throws {
		if ( mCurrentPos >= mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentPos + ") out of bounds");
		}

		mCurrentPos++;
	}

	public void reset(string value = "") modify {
		mCurrentPos = 0;
		mLength = strlen(value);
		mValue = value;
	}

	public void operator++() modify throws {
		if ( mCurrentPos >= mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentPos + ") out of bounds");
		}

		mCurrentPos++;
	}
}

