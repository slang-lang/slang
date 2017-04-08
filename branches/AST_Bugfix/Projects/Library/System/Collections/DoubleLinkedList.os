
import AbstractCollection;
import System.Exception;

public namespace System.Collections { }

/*
 * Double linked list
 * allows reverse iteration
 */
public object DoubleLinkedList extends AbstractCollection {
	public void Constructor() {
		base.Constructor();
	}

	public void pop_back() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("pop beyond begin of collection");
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
		}

		mSize--;
	}

	public void pop_front() modify throws {
		if ( mSize <= 0 ) {
			throw new OutOfBoundsException("pop beyond begin of collection");
		}

		mFirst = mFirst.mNext;

		mSize--;
	}

	public void push_back(Object value ref) modify {
		CollectionItem item = new CollectionItem(value);

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

	public void push_front(Object value ref) modify {
		CollectionItem item = new CollectionItem(value);

		item.mNext = mFirst;
		//mFirst.mPrevious = item;	// this leaves a mem leak... ;-(
		mFirst = item;

		mSize++;
	}
}

