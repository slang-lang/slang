
import System.Collections.CollectionItem;
import System.Collections.IIterateable;
import System.Collections.Iterator;
import System.Exception;
import ICollection;

public namespace System.Collections.Generics { }

public object Stack<T> implements ICollection {
	private CollectionItem mFirst;
	private CollectionItem mLast;
	private int mSize = 0;

	public void Constructor() {
	}

	public void Destructor() {
		clear();
	}

	public T at(int index) const throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException("index(" + index + ") out of bounds");
		}

		CollectionItem item = mFirst;
		for ( int i = 0; i < index; i = i++ ) {
			item = item.mNext;
		}

		return T item.mValue;
	}

	public void clear() modify {
		for ( int i = 0; i < mSize; i = i++ ) {
			mFirst.mValue = null;
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
			throw new OutOfBoundsException("erase index(" + index + ") beyond end of set");
		}

		if ( index == 0 ) {						// special handling for 1st element
			mFirst = mFirst.mNext;
		}
		else {									// default handling for erasing
			CollectionItem prev = mFirst;
			for ( int i = 0; i < index - 1; i = i++ ) {
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

	public Iterator getIterator() const {
		return new Iterator(ICollection this);
	}

	public ReverseIterator getReverseIterator() const {
		return new ReverseIterator(ICollection this);
	}

	public int indexOf(T value) const {
		CollectionItem item = mFirst;

		for ( int i = 0; i < mSize; i = i++ ) {
			if ( item.mValue == value ) {
				return i;
			}

			item = item.mNext;
		}

		return -1;
	}

	public T peek() const throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("stack underflow");
		}

		return T mLast.mValue;
	}

	public void pop() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("stack underflow");
		}

		if ( mSize == 1 ) {
			mFirst = CollectionItem null;
		}
		else {
			CollectionItem item = mFirst;
			for ( int i = 0; i < mSize - 1; i = i++ ) {
				item = item.mNext;
			}

			item.mNext = CollectionItem null;

			mLast = item;
		}

		mSize--;
	}

	public void push(T value) modify {
		CollectionItem item = new CollectionItem(Object value);

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

	public T operator[](int index) const throws {
		return at(index);
	}
}
