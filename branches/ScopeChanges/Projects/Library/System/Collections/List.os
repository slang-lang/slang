
import CollectionItem;
import ICollection;
import Iterator;
import System.Exception;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object List<T> implements ICollection {
	public void Constructor() {
		// this determines if we are dealing with an object type or a native data type
		T check;
		mIsObjectType = check is Object;
	}

	public void Destructor() {
		clear();
	}

	public T at(int index) const throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException("index(" + index + ") out of bounds");
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

	public bool contains(T value) const {
		return indexOf(value) != -1;
	}

	public bool empty() const {
		return mSize == 0;
	}

	public void erase(int index) modify throws {
		if ( index < 0 || index > mSize ) {
			throw new OutOfBoundsException("erase index(" + index + ") out of bounds");
		}

		if ( index == 0 ) {			// special handling for 1st element
			mFirst = mFirst.mNext;
		}
		else {					// default handling for erasing
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
	}

	public T first() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException("empty collection");
		}

		return mFirst.mValue;
	}

	public Iterator<T> getIterator() const {
		return new Iterator<T>(ICollection this);
	}

	public ReverseIterator<T> getReverseIterator() const {
		return new ReverseIterator<T>(ICollection this);
	}

	public int indexOf(T value) const {
		CollectionItem<T> item = mFirst;

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
			throw new OutOfBoundsException("empty collection");
		}

		return mLast.mValue;
	}

	public void pop_back() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("empty collection");
		}

		if ( mSize == 1 ) {			// special handling for 1st item
			delete mFirst;
			delete mLast;
		}
		else {					// generic handling
			CollectionItem<T> item = mFirst;
			for ( int i = 0; i < mSize - 1; i++ ) {
				item = item.mNext;
			}

			mLast = item;
			delete item.mNext;
		}

		mSize--;
	}

	public void pop_front() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("empty collection");
		}

		mFirst = mFirst.mNext;
		if ( !mFirst ) {
			delete mLast;
		}

		mSize--;
	}

	public void push_back(T value) modify {
		CollectionItem<T> item = new CollectionItem<T>(value);

		if ( mSize == 0 ) {			// special handling for 1st item
			mFirst = item;
		}
		else {					// generic handling
			mLast.mNext = item;
		}

		mLast = item;

		mSize++;
	}

	public void push_front(T value) modify {
		CollectionItem<T> item = new CollectionItem<T>(value);

		item.mNext = mFirst;
		mFirst = item;

		if ( mSize == 0 ) {
			mLast = item;
		}

		mSize++;
	}

	public int size() const {
		return mSize;
	}

	public T operator[](int index) const throws {
		return at(index);
	}

	private CollectionItem<T> mFirst;
	private bool mIsObjectType;
	private CollectionItem<T> mLast;
	private int mSize = 0;

	private Iterator<T> __iterator;				// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;		// this is a hack to automatically initialize a generic type
}

