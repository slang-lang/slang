
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object List<T> implements ICollection {
	public void Constructor() {
		// nothing to do here
	}

	public void Destructor() {
		clear();
	}

	public List<T> Copy() const {
		var result = new List<T>();

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
			item = item.next;
		}

		return item.value;
	}

	public void clear() modify {
		for ( int i = 0; i < mSize; i++ ) {
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
			throw new OutOfBoundsException( "erase index(" + index + ") out of bounds" );
		}

		if ( index == 0 ) {						// special handling for 1st element
			mFirst = mFirst.next;
		}
		else if ( index == mSize - 1 ) {		// special handling for last element
			var prev = mFirst;

			while( prev.next.next )
				prev = prev.next;

			prev.next = CollectionItem<T> null;
			mLast = prev;
		}
		else {									// default handling for erasing
			var prev = mFirst;

			for ( int i = 0; i < index - 1; i++ ) {
				prev = prev.next;
			}

			if ( index == mSize - 1 ) {
				mLast = prev.next;
			}
			else if ( prev.next ) {
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
		CollectionItem<T> item = mFirst;

		for ( int i = 0; i < mSize; i++ ) {
			if ( item.value == value ) {
				return i;
			}

			item = item.next;
		}

		return -1;
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

		if ( mSize == 1 ) {			// special handling for 1st item
			delete mFirst;
			delete mLast;
		}
		else {					// generic handling
			CollectionItem<T> item = mFirst;
			for ( int i = 0; i < mSize - 1; i++ ) {
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

		if ( mSize == 0 ) {			// special handling for 1st item
			mFirst = item;
		}
		else {						// generic handling
			mLast.next = item;
		}

		item.previous = mLast;
		mLast = item;

		mSize++;
	}

	public void push_front( T value ) modify {
		var item = new CollectionItem<T>( value );

		if ( mSize == 0 ) {			// special handling for 1st item
			mLast = item;
		}
		else {						// generic handling
			item.next = mFirst;
			mFirst.previous = item;
		}

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
	private int mSize;

	private Iterator<T> __iterator;					// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;	// this is a hack to automatically initialize a generic type
}

