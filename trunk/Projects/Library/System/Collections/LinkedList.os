
import IIterateable;
import System.Exception;

public namespace System {

public object LinkedItem {
	private LinkedItem mNext;
	private Object mValue;

	public void LinkedItem() {
	}

	public void LinkedItem(Object value ref) {
		mValue = value;
	}

	public Object get() const {
		return mValue;
	}

	public LinkedItem next() const {
		return mNext;
	}

	public void set(Object value ref) modify {
		mValue = value;
	}
}

public object LinkedList implements IIterateable {
	private int mCount;
	private int mCurrentIdx;
	private LinkedItem mFirst;
	private LinkedItem mLast;

	public void LinkedList() {
		mCount = 0;
		mCurrentIdx = -1;
	}

	public Object at(int index) const {
		if ( index < 0 || index >= mCount ) {
			throw new System.OutOfBoundsException("index " + index + " out of bounds");
		}

		LinkedItem item = mFirst;
		for ( int i = 0; i < index; i = i++ ) {
			item = item.mNext;
			//item = item.next();
		}

		return item.mValue;
		//return item.get();
	}

	public Object current() const {
		return at(mCurrentIdx);
	}

	public void erase(int index) modify {
		if ( index > mCount ) {
			throw new System.OutOfBoundsException("erase index(" + index + ") beyond end of list");
		}

		assert(!"not implemented!");

		LinkedItem item = mFirst;
		for ( int i = 0; i < mCount; i = i++ ) {
			if ( i == index ) {
			}

			item = item.mNext;
		}
	}

	public void insert(Object value ref, int index) modify {
		if ( index > mCount ) {
			throw new System.OutOfBoundsException("insert index(" + index + ") beyond end of list");
		}

		LinkedItem item = new LinkedItem(value);

		if ( index == 0 ) {	// special handling for 1st element
			item.mNext = mFirst;
			mFirst = item;
		}
		else {	// default handling for insertions
			LinkedItem tmp = mFirst;
			for ( int i = 0; i < mCount; i = i++ ) {
				if ( i == index ) {
					item.next = tmp.mNext;
					tmp.mNext = item;
					break;
				}

				tmp = tmp.mNext;
			}
		}

		mCount++;
	}

	public bool hasNext() const {
		return mCurrentIdx < mCount - 1;
	}

	public void next() modify {
		mCurrentIdx++;
	}

	public void push_back(Object value ref) modify {
		LinkedItem item = new LinkedItem();
		item.mValue = value;

		if ( mCount == 0 ) {
			mFirst = item;
		}
		else {
			mLast.mNext = item;
		}

		mLast = item;

		mCount++;
	}

	public void push_front(Object value ref) modify {
		LinkedItem item = new LinkedItem(value);

		item.mNext = mFirst;
		mFirst = item;

		mCount++;
	}

	public void reset() modify {
		mCurrentIdx = -1;
	}

	public int size() const {
		return mCount;
	}
}

}

