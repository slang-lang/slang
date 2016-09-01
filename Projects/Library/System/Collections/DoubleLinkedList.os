
import IIterateable;
import System.Exception;

public namespace System {

public object DoubleLinkedItem {
	private DoubleLinkedItem mNext;
	private DoubleLinkedItem mPrevious;
	private Object mValue;

	public Object get() const {
		return mValue;
	}

	public DoubleLinkedItem next() const {
		return mNext;
	}

	public void set(Object value ref) modify {
		mValue = value;
	}
}

public object DoubleLinkedList implements IReverseIterateable {
	private int mCount;
	private int mCurrentIdx;
	private DoubleLinkedItem mFirst;
	private DoubleLinkedItem mLast;

	public void DoubleLinkedList() {
		mCount = 0;
		mCurrentIdx = -1;
	}

	public Object at(int index) const {
		if ( index < 0 || index >= mCount ) {
			throw new System.OutOfBoundsException("index " + index + " out of bounds");
		}

		DoubleLinkedItem item = mFirst;
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

	public bool hasNext() const {
		return mCurrentIdx < mCount;
	}

	public bool hasPrevious() const {
		return mCurrentIdx > 0;
	}

	public void next() modify {
		mCurrentIdx++;
	}

	public void previous() modify {
		mCurrentIdx--;
	}

	public void push(Object value ref) modify {
		DoubleLinkedItem item = new DoubleLinkedItem();
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

	public void reset() modify {
		mCurrentIdx = -1;
	}

	public int size() const {
		return mCount;
	}
}

}

