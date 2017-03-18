
import AbstractCollection;
import System.Exception;

public namespace System.Collections { }

public object Stack extends AbstractCollection {
	public void Constructor() {
		base.Constructor();
	}

	public bool empty() const {
		return mSize == 0;
	}

	public Object peek() const throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("stack underflow");
		}

		return mLast.mValue;
	}

	public void pop() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("stack underflow");
		}

		if ( mSize == 1 ) {
			mFirst = null;
		}
		else {
			CollectionItem item = mFirst;
			for ( int i = 0; i < mSize - 1; i = i++ ) {
				item = item.mNext;
			}

			item.mNext = null;

			mLast = item;
		}

		mSize--;
	}

	public void push(Object value ref) modify {
		CollectionItem item = new CollectionItem(value);

		if ( mSize == 0 ) {		// special handling for 1st item
			mFirst = item;
		}
		else {					// generic handling
			mLast.mNext = item;
		}

		mLast = item;

		mSize++;
	}
}

