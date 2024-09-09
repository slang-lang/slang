
import System.Exception;
import ICollection;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object RandomAccessIterator<T> {
	public void Constructor( ICollection collection const ) {
		mCollection = collection;

		reset();
	}

	public T current() const throws {
		if ( !mCollection ) {
			throw new Exception( "current(): invalid iterator access" );
		}
		if ( mCurrentIndex == -1 ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		return T mCollection.at( mCurrentIndex );
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception( "hasNext(): invalid iterator access" );
		}

		return (mCurrentIndex + 1) < mCollection.size();
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException( "next(): index out of bounds" );
		}

		mCurrentIndex++;

		return T mCollection.at( mCurrentIndex );
	}

	public T peek( int offset = 1 ) const throws {
		return T mCollection.at( mCurrentIndex + offset );
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	public bool operator==( RandomAccessIterator<T> other const ) const {
		return mCurrentIndex == other.mCurrentIndex;
	}

	public T =operator( T ) const throws {
		return current();
	}

	public T operator++() modify throws {
		return next();	
	}

	private ICollection mCollection const;
	private int mCurrentIndex;
}

public object ReverseRandomAccessIterator<T> {
	public void Constructor( ICollection collection const ) {
		mCollection = collection;

		reset();
	}

	public T current() const throws {
		if ( !mCollection ) {
			throw new Exception( "current(): invalid iterator access" );
		}
		if ( mCurrentIndex == mCollection.size() ) {
			throw new Exception ("current(): iterator not initialized" );
		}

		return T mCollection.at( mCurrentIndex );
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception( "hasNext(): invalid iterator access" );
		}

		return mCurrentIndex > 0;
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException( "next(): index out of bounds" );
		}

		mCurrentIndex--;

		return T mCollection.at( mCurrentIndex );
	}

	public T peek( int offset = 1 ) const throws {
		return T mCollection.at( mCurrentIndex + offset );
	}

	public void reset() modify {
		mCurrentIndex = mCollection.size();
	}

	public bool operator==( ReverseRandomAccessIterator<T> other const ) const {
		return mCurrentIndex == other.mCurrentIndex;
	}

	public T =operator( T ) const throws {
		return current();
	}

	public T operator++() modify throws {
		return next();		
	}

	private ICollection mCollection const;
	private int mCurrentIndex;
}

