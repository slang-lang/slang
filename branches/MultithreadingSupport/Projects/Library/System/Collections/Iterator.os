
import ICollection;
import System.Exception;

public namespace System.Collections { }

public object Iterator {
	private ICollection mCollection;
	private int mCurrentIndex;

	public void Constructor(ICollection collection ref) {
		mCollection = collection;

		reset();
	}

	public Object current() const throws {
		if ( !mCollection ) {
			throw new Exception("current(): invalid iterator access");
		}
		if ( mCurrentIndex == -1 ) {
			throw new Exception("iterator not initialized");
		}

		return mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("hasNext(): invalid iterator access");
		}

		return mCurrentIndex < mCollection.size() - 1;
	}

	public Object next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("next(): index out of bounds");
		}

		mCurrentIndex++;

		return mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	public Object =operator(Object none ref) const throws {
		return current();
	}

	public void operator++() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("operator++(): index out of bounds");
		}

		mCurrentIndex++;		
	}
}

public object ReverseIterator {
	private ICollection mCollection;
	private int mCurrentIndex;

	public void Constructor(ICollection collection ref) {
		mCollection = collection;

		reset();
	}

	public Object current() const throws {
		if ( !mCollection ) {
			throw new Exception("current(): invalid iterator access");
		}
		if ( mCurrentIndex == mCollection.size() ) {
			throw new Exception("iterator not initialized");
		}

		return mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("hasNext(): invalid iterator access");
		}

		return mCurrentIndex > 0;
	}

	public Object next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("next(): index out of bounds");
		}

		mCurrentIndex--;

		return mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = mCollection.size();
	}

	public Object =operator(Object none ref) const throws {
		return current();
	}

	public void operator++() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("operator++(): index out of bounds");
		}

		mCurrentIndex--;		
	}
}

