
import System.Collections.Iterator;

public object CharacterIterator implements Iterator {
	private int mCurrentIndex;
	private int mLength;
	private string mValue;

	public void Constructor(string value = "") {
		reset(value);
	}

	public string current() const throws {
		if ( mCurrentIndex < 0 ) {
			throw new NotInitializedException("iterator not initialized");
		}
		if ( !mValue ) {
			throw new Exception("invalid iteration string");
		}

		return substr(mValue, mCurrentIndex, 1);
	}

	public bool hasNext() const {
		return mCurrentIndex < mLength;
	}

	public string lookAHead(int offset = 1) const throws {
		if ( offset <= 0 ) {
			throw new Exception("invalid look ahead offset(" + offset + ")");
		}
		if ( mCurrentIndex + offset >= mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + offset + ") out of bounds");
		}

		return substr(mValue, mCurrentIndex + offset, 1);
	}

	public string next() modify throws {
		if ( mCurrentIndex >= mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + ") out of bounds");
		}

		mCurrentIndex++;
		return substr(mValue, mCurrentIndex, 1);
	}

	public void reset(string value = "") modify {
		mCurrentIndex = -1;
		mLength = strlen(value);
		mValue = value;
	}

	public string =operator(string none) const throws {
		if ( !mValue ) {
			throw new Exception("invalid iteration string");
		}

		return substr(mValue, mCurrentIndex, 1);
	}

	public void operator++() modify throws {
		if ( mCurrentIndex >= mLength ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + ") out of bounds");
		}

		mCurrentIndex++;
	}
}

