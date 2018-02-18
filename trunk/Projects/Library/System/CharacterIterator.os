
import System.Collections.Iterator;

public object CharacterIterator implements Iterator {
	private int mCurrentIndex;
	private int mLength;
	private string mValue;

	public void Constructor(string value = "") {
		reset(value);
	}

	public string current() const throws {
		if ( !mValue ) {
			throw new Exception("invalid iteration string");
		}

		return substr(mValue, mCurrentIndex, 1);
	}

	public bool hasNext() const {
		return mCurrentIndex < mLength;
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

