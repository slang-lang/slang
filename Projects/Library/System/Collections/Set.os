
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Set<T> implements ICollection {
	public void Constructor( bool allowDuplicates = false ) {
		mAllowDuplicates = allowDuplicates;
	}

	public void Destructor() {
		clear();
	}

	public Set<T> Copy() const {
		var result = new Set<T>();

		result.mAllowDuplicates = mAllowDuplicates;
		result.mFirst = mFirst;
		result.mLast = mLast;
		result.mSize = mSize;

		return result;
	}

	public T at( int index ) const throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException( "index(" + index + ") out of bounds" );
		}

		CollectionItem<T> item = mFirst;
		for ( int i = 0; i < index; i++ ) {
			item = item.mNext;
		}

		return item.mValue;
	}

	public void clear() modify {
		for ( int i = 0; i < mSize; i++ ) {
			delete mFirst.mValue;
			mFirst = mFirst.mNext;
		}

		mSize = 0;
	}

	public bool contains( T value ) const {
		return indexOf( value ) != -1;
	}

	public bool empty() const {
		return mSize == 0;
	}

	public void erase( int index ) modify throws {
		if ( index < 0 || index > mSize ) {
			throw new OutOfBoundsException( "index(" + index + ") out of bounds" );
		}

		if ( index == 0 ) {						// special handling for 1st element
			mFirst = mFirst.mNext;
		}
		else {									// default handling for erasing
			CollectionItem<T> prev = mFirst;
			for ( int i = 0; i < index - 1; i++ ) {
				prev = prev.mNext;
			}

			if ( index == mSize - 1 ) {
				mLast = prev;
			}
			else if ( prev.mNext ) {
				prev.mNext = prev.mNext.mNext;
			}
		}

		mSize--;

		if ( mSize == 0 ) {
			mFirst = CollectionItem<T> null;
			mLast = mFirst;
		}
	}

	public T first() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		return mFirst.mValue;
	}

	public Iterator<T> getIterator() const {
		return new Iterator<T>( cast<ICollection>( this ) );
	}

	public ReverseIterator<T> getReverseIterator() const {
		return new ReverseIterator<T>( cast<ICollection>( this ) );
	}

	public int indexOf( T value ) const {
		CollectionItem<T> item = mFirst;

		for ( int i = 0; i < mSize; i++ ) {
			if ( item.mValue == value ) {
				return i;
			}

			item = item.mNext;
		}

		return -1;
	}

	public void insert (T value ) modify throws {
		var item = new CollectionItem<T>( value );

		if ( !mFirst ) {				// special handling for 1st element
			mFirst = item;
			mLast = item;
		}
		else if ( (T value) < (T mFirst.mValue) ) {		// special handling for inserting in 1st position
			item.mNext = mFirst;
			mFirst = item;
		}
		else {						// default handling for insertions
			var tmp = mFirst;
			CollectionItem<T> previous;

			for ( int i = 0; i < mSize; i++ ) {
				if ( (T value) < (T tmp.mValue) ) {
					break;
				}

				previous = tmp;
				tmp = tmp.mNext;
			}

			if ( !mAllowDuplicates ) {
				if ( previous.mNext ) {
					if ( item == previous.mNext ) {
						throw new Exception("duplicate item");
					}
				}
			}

			item.mNext = previous.mNext;
			previous.mNext = item;
		}

		mSize++;
	}

	public T last() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		return mLast.mValue;
	}

	public int size() const {
		return mSize;
	}

	public T operator[]( int index ) const throws {
		return at( index );
	}

	private bool mAllowDuplicates;
	private CollectionItem<T> mFirst;
	private CollectionItem<T> mLast;
	private int mSize;

	private Iterator<T> __iterator;				// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;		// this is a hack to automatically initialize a generic type
}

