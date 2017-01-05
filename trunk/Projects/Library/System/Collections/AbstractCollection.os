
import IIterateable;
import Iterator;

public namespace System.Collections { }

/*
 * Double linked collection item
 */
public object CollectionItem {
	public CollectionItem mNext;
	public CollectionItem mPrevious;
	public Object mValue;

	public void Constructor() {
		// this is empty by intend
	}

	public void Constructor(Object value ref) {
		mValue = value;
	}

	public void Destructor() {
		// this is empty by intend
	}

	public Object get() const {
		return mValue;
	}

	public CollectionItem next() const {
		return mNext;
	}

	public CollectionItem previous() const {
		return mPrevious;
	}

	public void set(Object value ref) modify {
		mValue = value;
	}
}

/*
	* Abstract base for collections
	*/
public abstract object AbstractCollection implements IIterateable {
	protected CollectionItem mFirst;
	protected CollectionItem mLast;
	protected int mSize = 0;

	public void Constructor() {
		mSize = 0;
	}
	public void Destructor() {
		clear();
	}

	public Object at(int index) const throws {
		if ( index < 0 || index >= mSize ) {
			throw new OutOfBoundsException("index(" + index + ") out of bounds");
		}

		CollectionItem item = mFirst;
		for ( int i = 0; i < index; i = i++ ) {
			item = item.mNext;
		}

		return item.mValue;
	}

	public void clear() modify {
		for ( int i = 0; i < mSize; i = i++ ) {
			mFirst.mValue = null;
			mFirst = mFirst.mNext;
		}

		mSize = 0;
	}

	public bool contains(Object value ref) const {
		return indexOf(value) != -1;
	}

	public bool empty() const {
		return mSize == 0;
	}

	public Object first() const {
		if ( empty() ) {
			throw new OutOfBoundsException("index(" + index + ") out of bounds");
		}

		return mFirst.mValue;
	}

	public Iterator getIterator() const {
		return new Iterator(AbstractCollection this);
	}

	public ReverseIterator getReverseIterator() const {
		return new ReverseIterator(AbstractCollection this);
	}

	public Object last() const {
		if ( empty() ) {
			throw new OutOfBoundsException("index(" + index + ") out of bounds");
		}

		return mLast.mValue;
	}

	public int indexOf(Object value ref) const {
		CollectionItem item = mFirst;
		for ( int i = 0; i < mSize; i = i++ ) {
			if ( item.mValue == value ) {
				return i;
			}

			item = item.mNext;
		}

		return -1;
	}

	public int size() const {
		return mSize;
	}

	public Object operator[](int index) const throws {
		return at(index);
	}
}

