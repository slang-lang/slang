
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Stack<T> implements ICollection {
	public void Constructor() {
		// nothing to do here
	}

	public void Destructor() {
		clear();
	}

	public Stack<T> Copy() const {
		var result = new Stack<T>();

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
		for ( int i = 0; i < mSize; i = i++ ) {
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

	public Iterator<T> getIterator() const {
		return new Iterator<T>( ICollection this );
	}

	public ReverseIterator<T> getReverseIterator() const {
		return new ReverseIterator<T>( ICollection this );
	}

	public int indexOf(T value) const {
		var item = mFirst;

		for ( int i = 0; i < mSize; i++ ) {
			if ( item.mValue == value ) {
				return i;
			}

			item = item.mNext;
		}

		return -1;
	}

	public T peek() const throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		return mLast.mValue;
	}

	public T pop() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		var last = mLast.mValue;

		if ( mSize == 1 ) {
			delete mFirst;
		}
		else {
			var item = mFirst;
			for ( int i = 0; i < mSize - 1; i++ ) {
				item = item.mNext;
			}

			delete item.mNext;

			mLast = item;
		}

		mSize--;

		return last;
	}

	public void push( T value ) modify {
		var item = new CollectionItem<T>( value );

		if ( mSize == 0 ) {			// special handling for 1st item
			mFirst = item;
		}
		else {						// generic handling
			mLast.mNext = item;
		}

		mLast = item;

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

	private Iterator<T> __iterator;				// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;		// this is a hack to automatically initialize a generic type
}

