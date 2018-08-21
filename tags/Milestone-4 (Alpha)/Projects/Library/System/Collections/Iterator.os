
import ICollection;
import System.Exception;

public namespace System.Collections { }

public object Iterator<T> {
	private ICollection mCollection;
	private int mCurrentIndex;

	public void Constructor(ICollection collection ref) {
		mCollection = collection;

		reset();
	}

	public T current() const throws {
		if ( !mCollection ) {
			throw new Exception("current(): invalid iterator access");
		}
		if ( mCurrentIndex == -1 ) {
			throw new Exception("iterator not initialized");
		}

		return T mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("hasNext(): invalid iterator access");
		}

		return mCurrentIndex < mCollection.size() - 1;
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("next(): index out of bounds");
		}

		mCurrentIndex++;

		return T mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	public T =operator(T) const throws {
		return current();
	}

	public T operator++() modify throws {
		return next();	
	}
}

public object ReverseIterator<T> {
	private ICollection mCollection;
	private int mCurrentIndex;

	public void Constructor(ICollection collection ref) {
		mCollection = collection;

		reset();
	}

	public T current() const throws {
		if ( !mCollection ) {
			throw new Exception("current(): invalid iterator access");
		}
		if ( mCurrentIndex == mCollection.size() ) {
			throw new Exception("iterator not initialized");
		}

		return T mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("hasNext(): invalid iterator access");
		}

		return mCurrentIndex > 0;
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("next(): index out of bounds");
		}

		mCurrentIndex--;

		return T mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = mCollection.size();
	}

	public T =operator(T) const throws {
		return current();
	}

	public T operator++() modify throws {
		return next();		
	}
}

