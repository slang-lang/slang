
import AbstractCollection;
import System.Exception;

public namespace System.Collections { }

public object Iterator {
	private AbstractCollection mCollection;
	private int mCurrentIndex;

	public void Constructor(AbstractCollection collection ref) {
		mCollection = collection;

		reset();
	}

	public Object current() const throws {
		if ( !mCollection ) {
			throw new Exception("invalid iterator access");
		}

		return mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("invalid iterator access");
		}

		return mCurrentIndex < mCollection.size() - 1;
	}

	public Object next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("index out of bounds");
		}

		mCurrentIndex++;

		return mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	public void operator++() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("index out of bounds");
		}

		mCurrentIndex++;		
	}

	public Object =operator(Object none ref) const {
		return current();
	}
}

public object ReverseIterator {
	private AbstractCollection mCollection;
	private int mCurrentIndex;

	public void Constructor(AbstractCollection collection ref) {
		mCollection = collection;

		reset();
	}

	public Object current() const throws {
		if ( !mCollection ) {
			throw new Exception("invalid iterator access");
		}

		return mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("invalid iterator access");
		}

		return mCurrentIndex > 0;
	}

	public Object next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("index out of bounds");
		}

		mCurrentIndex--;

		return mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = mCollection.size();
	}

	public void operator++() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("index out of bounds");
		}

		mCurrentIndex--;		
	}

	public Object =operator(Object none ref) const {
		return current();
	}
}

