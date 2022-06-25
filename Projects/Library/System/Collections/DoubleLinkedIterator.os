
import System.Exception;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Iterator<T> {
	public void Constructor( CollectionItem<T> first ) {
		mCurrentItem = first;
		mFirstItem   = first;
	}

	public T current() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		return T mCurrentItem.value;
	}

	public bool hasNext() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}
		if ( mCurrentItem ) {
			return bool mCurrentItem.next;
		}

		return false;
	}

	public bool hasPrevious() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}
		if ( mCurrentItem ) {
			return bool mCurrentItem.previous;
		}

		return false;
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException( "next(): index out of bounds" );
		}

		mCurrentItem = mCurrentItem.next;

		return T mCurrentItem.value;
	}

	public T peek( int offset = 1 ) const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		var tmpItem = mCurrentItem;

		if ( offset > 0 ) {
			while ( offset-- > 0 ) {
				tmpItem = tmpItem.next;
			}
		}
		else if ( offset < 0 ) {
			while ( offset++ < 0 ) {
				tmpItem = tmpItem.previous;
			}
		}

		return T tmpItem.value;
	}

	public T previous() modify throws {
		if ( !hasPrevious() ) {
			throw new OutOfBoundsException( "previous(): index out of bounds" );
		}

		mCurrentItem = mCurrentItem.previous;

		return T mCurrentItem.value;
	}

	public void reset() modify throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		mCurrentItem = mFirstItem;
	}

	public bool operator==( Iterator<T> other const ) const {
		return mCurrentItem == other.mCurrentItem;
	}

	public T =operator( T ) const throws {
		return current();
	}

	public T operator++() modify throws {
		return next();	
	}

	private CollectionItem<T> mCurrentItem;
	private CollectionItem<T> mFirstItem;
}



public object ReverseIterator<T> {
	public void Constructor( CollectionItem<T> last ) {
		mCurrentItem = last;
		mLastItem    = last;
	}

	public T current() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		return T mCurrentItem.value;
	}

	public bool hasNext() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}
		if ( mCurrentItem ) {
			return bool mCurrentItem.previous;
		}

		return false;
	}

	public bool hasPrevious() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}
		if ( mCurrentItem ) {
			return bool mCurrentItem.next;
		}

		return false;
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException( "next(): index out of bounds" );
		}

		mCurrentItem = mCurrentItem.previous;

		return T mCurrentItem.value;
	}

	public T peek( int offset = 1 ) const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		var tmpItem = mCurrentItem;

		if ( offset > 0 ) {
			while ( offset-- > 0 ) {
				tmpItem = tmpItem.previous;
			}
		}
		else if ( offset < 0 ) {
			while ( offset++ < 0 ) {
				tmpItem = tmpItem.next;
			}
		}

		return T tmpItem.value;
	}

	public T previous() modify throws {
		if ( !hasPrevious() ) {
			throw new OutOfBoundsException( "previous(): index out of bounds" );
		}

		mCurrentItem = mCurrentItem.next;

		return T mCurrentItem.value;
	}

	public void reset() modify throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		mCurrentItem = mLastItem;
	}

	public bool operator==( ReverseIterator<T> other const ) const {
		return mCurrentItem == other.mCurrentItem;
	}

	public T =operator( T ) const throws {
		return current();
	}

	public T operator++() modify throws {
		return next();		
	}

	private CollectionItem<T> mCurrentItem;
	private CollectionItem<T> mLastItem;
}

