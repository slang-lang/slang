
import System.Collections.CollectionItem;
import System.Collections.ICollection;
import System.Collections.Iterator;
import System.Exception;

public namespace System.Collections.Generics { }

public object Set<T> implements ICollection {
	private bool mAllowDuplicates;
	private CollectionItem mFirst;
	private CollectionItem mLast;
	private int mSize = 0;

	public void Constructor(bool allowDuplicates = false) {
		mAllowDuplicates = allowDuplicates;
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

	public T first() const throws {
		if ( !mSize ) {
			throw new OutOfBoundsException("empty collection");
		}

		return T mFirst.mValue;
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

	public void insert(T value) modify throws {
		CollectionItem item = new CollectionItem(Object value);

		if ( !mFirst ) {				// special handling for 1st element
			mFirst = item;
			mLast = item;
		}
		else if ( value < mFirst.mValue ) {		// special handling for inserting in 1st position
			item.mNext = mFirst;
			mFirst = item;
		}
		else {						// default handling for insertions
			CollectionItem tmp = mFirst;
			CollectionItem previous;

			for ( int i = 0; i < mSize; i = i++ ) {
				if ( value < tmp.mValue ) {
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
			throw new OutOfBoundsException("empty collection");
		}

		return T mLast.mValue;
	}

	public int size() const {
		return mSize;
	}

	public T operator[](int index) const throws {
		return at(index);
	}
}


