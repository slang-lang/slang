
import System.Exception;
import CollectionItem;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Iterator<T> {
	public void Constructor( CollectionItem<T> first const ) {
		mFirstItem = first;
	}

	public T current() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		return T mCurrentItem.value;
	}

	public bool hasNext() const throws {
		if ( !mFirstItem ) {
			//throw new Exception( "current(): iterator not initialized" );
			return false;
		}
		if ( !mCurrentItem ) {
			return bool mFirstItem;
		}

		return bool mCurrentItem.next;
	}

	public bool hasPrevious() const throws {
		if ( !mFirstItem ) {
			//throw new Exception( "current(): iterator not initialized" );
			return false;
		}
		if ( !mCurrentItem ) {
			return bool mFirstItem;
		}

		return bool mCurrentItem.previous;
	}

	public T next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException( "next(): index out of bounds" );
		}

		if ( !mCurrentItem ) {
			mCurrentItem = mFirstItem;
		}
		else {
			mCurrentItem = mCurrentItem.next;
		}

		return T mCurrentItem.value;
	}

	public T peek( int offset = 1 ) const throws {
		if ( !mCurrentItem && !mFirstItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		var tmpItem = mCurrentItem;

		if ( offset > 0 ) {
			while ( offset-- >= 0 ) {
				tmpItem = tmpItem.next;
			}
		}
		else if ( offset < 0 ) {
			while ( offset++ <= 0 ) {
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
		// if ( !mCurrentItem ) {
		// 	throw new Exception( "current(): iterator not initialized" );
		// }

		mCurrentItem = CollectionItem<T> null;
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

	public T operator--() modify throws {
		return previous();
	}

	private CollectionItem<T> mCurrentItem;
	private CollectionItem<T> mFirstItem;
}


public object ReverseIterator<T> {
	public void Constructor( CollectionItem<T> last const ) {
		mLastItem = last;
	}

	public T current() const throws {
		if ( !mCurrentItem ) {
			throw new Exception( "current(): iterator not initialized" );
		}

		return T mCurrentItem.value;
	}

	public bool hasNext() const throws {
		if ( !mLastItem ) {
			//throw new Exception( "current(): iterator not initialized" );
			return false;
		}
		if ( !mCurrentItem ) {
			return bool mLastItem;
		}

		return bool mCurrentItem.previous;
	}

	public bool hasPrevious() const throws {
		if ( !mLastItem ) {
			//throw new Exception( "current(): iterator not initialized" );
			return false;
		}
		if ( !mCurrentItem ) {
			return bool mLastItem;
		}

		return bool mCurrentItem.next;
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
		// if ( !mCurrentItem ) {
		// 	throw new Exception( "current(): iterator not initialized" );
		// }

		mCurrentItem = CollectionItem<T> null;
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

	public T operator--() modify throws {
		return previous();
	}

	private CollectionItem<T> mCurrentItem;
	private CollectionItem<T> mLastItem;
}

