
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

/*
 * Double linked list
 * allows reverse iteration
 */
public object DoubleLinkedList<T> implements ICollection {
	public void Constructor() {
	}

	public void Destructor() {
		clear();
	}

	public DoubleLinkedList<T> Copy() const {
		var result = new DoubleLinkedList<T>();

		result.mFirst = mFirst;
		result.mLast = mLast;
		result.mSize = mSize;

		return result;
	}

	public T at( int index ) const throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException( "index(" + index + ") out of bounds" );
		}

		var item = mFirst;
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
			var prev = mFirst;
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
	}

	public T first() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		return mFirst.mValue;
	}

	public Iterator<T> getIterator() const {
		return new Iterator<T>( ICollection this );
	}

	public ReverseIterator<T> getReverseIterator() const {
		return new ReverseIterator<T>( ICollection this );
	}

	public int indexOf( T value ) const {
		var item = mFirst;

		for ( int i = 0; i < mSize; i++ ) {
			if ( item.mValue == value ) {
				return i;
			}

			item = item.mNext;
		}

		return -1;
	}

	public T last() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		return mLast.mValue;
	}

	public void pop_back() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		if ( mSize == 1 ) {
			delete mFirst;
		}
		else {
			var item = mFirst;
			for ( int i = 0; i < mSize - 1; i++ ) {
				item = item.mNext;
			}

			delete item.mNext;
		}

		mSize--;
	}

	public void pop_front() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		mFirst = mFirst.mNext;

		mSize--;
	}

	public void push_back( T value ) modify {
		var item = new CollectionItem<T>( value );

		if ( mSize == 0 ) {
			mFirst = item;
		}
		else {
			mLast.mNext = item;
		}

		//item.mPrevious = mLast;	// this leaves a mem leak... ;-(
		mLast = item;

		mSize++;
	}

	public void push_front( T value ) modify {
		var item = new CollectionItem<T>( value );
		item.mNext = mFirst;

		//mFirst.mPrevious = item;	// this leaves a mem leak... ;-(
		mFirst = item;

		mSize++;
	}

	public int size() const {
		return mSize;
	}

	public T operator[]( int index ) const throws {
		return at( index );
	}

	private CollectionItem<T> mFirst;
	private CollectionItem<T> mLast;
	private int mSize = 0;

	private Iterator<T> __iterator;						// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;		// this is a hack to automatically initialize a generic type
}

