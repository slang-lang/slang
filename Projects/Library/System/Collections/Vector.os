
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Vector<T> implements ICollection {
	public void Constructor() {
		// nothing to do here
	}

	public void Destructor() {
		clear();
	}

	public Vector<T> Copy() const {
		var result = new Vector<T>();

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
		for ( int idx = 0; idx < index; idx++ ) {
			item = item.next;
		}

		return item.value;
	}

	public void clear() modify {
		for ( int idx = 0; idx < mSize; idx++ ) {
			delete mFirst.value;
			mFirst = mFirst.next;
		}

		mFirst = CollectionItem<T> null;
		mLast = CollectionItem<T> null;
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
			throw new OutOfBoundsException( "erase index(" + index + ") beyond end of list" );
		}

		if ( index == 0 ) {	            // special handling for 1st element
			mFirst = mFirst.next;
		}
		else if ( index == mSize - 1 ) {	// special handling for last element
			if ( mLast.previous ) {
				mLast = mLast.previous;
			}
		}
		else {	                        // default handling for erasing
			var prev = mFirst;
			for ( int idx = 0; idx < index - 1; idx++ ) {
				prev = prev.next;
			}

			if ( index == mSize - 1 ) {
				mLast = prev;
			}
			else {
				prev.next = prev.next.next;
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

		return mFirst.value;
	}

///* activate for double linked iterator usage
	public Iterator<T> getIterator() const {
		return new Iterator<T>( mFirst );
	}

	public ReverseIterator<T> getReverseIterator() const {
		return new ReverseIterator<T>( mLast );
	}
//*/

/* activate for random access iterator usage
	public Iterator<T> getIterator() const {
		return new Iterator<T>( ICollection this );
	}

	public ReverseIterator<T> getReverseIterator() const {
		return new ReverseIterator<T>( ICollection this );
	}
*/

	public int indexOf( T value ) const {
		var item = mFirst;

		for ( int idx = 0; idx < mSize; idx++ ) {
			if ( item.value == value ) {
				return idx;
			}

			item = item.next;
		}

		return -1;
	}

	public void insert( int index, T value ) modify throws {
		if ( index < 0 || index > mSize ) {
			throw new OutOfBoundsException( "insert index(" + index + ") beyond end of list" );
		}

		var item = new CollectionItem<T>( value );

		if ( !mFirst ) {
			mFirst = item;
			mLast = item;
		}
		else if ( index == 0 ) {		// special handling for 1st element
			item.next = mFirst;
			mFirst = item;
		}
		else if ( index == mSize ) {		// special handling for last element
			mLast.next = item;
			mLast = item;
		}
		else {					// default handling for insertions
			var tmp = mFirst;
			for ( int idx = 0; idx < index - 1; idx++ ) {
				tmp = tmp.next;
			}

			item.next = tmp.next;
			tmp.next = item;
		}

		mSize++;
	}

	public T last() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		return mLast.value;
	}

	public void pop_back() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		if ( mSize == 1 ) {                     // special handling for 1st item
			delete mFirst;
			delete mLast;
		}
		else {                                  // generic handling
			var item = mFirst;
			for ( int idx = 0; idx < mSize - 1; idx++ ) {
				item = item.next;
			}

			mLast = item;
			delete item.next;
		}

		mSize--;
	}

	public void pop_front() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		mFirst = mFirst.next;
		if ( !mFirst ) {
			delete mLast;
		}

		mSize--;
	}

	public void push_back( T value ) modify {
		var item = new CollectionItem<T>( value );

		if ( mSize == 0 ) {                     // special handling for 1st item
			mFirst = item;
		}
		else {                                  // generic handling
			mLast.next = item;
		}

		mLast = item;

		mSize++;
	}

	public void push_front( T value ) modify {
		var item = new CollectionItem<T>( value );

		item.next = mFirst;
		mFirst = item;

		if ( mSize == 0 ) {
			mLast = item;
		}

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

	private Iterator<T> __iterator;					// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;	// this is a hack to automatically initialize a generic type
}

