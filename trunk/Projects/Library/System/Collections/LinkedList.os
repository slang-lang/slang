
import IIterateable;
import System.Exception;

public namespace System {

public object ListItem {
	private ListItem mNext;
	private Object mValue;

	public Object get() const {
		return mValue;
	}

	public ListItem next() const {
		return mNext;
	}

	public void set(Object value ref) modify {
		mValue = value;
	}
}

public object LinkedList implements IIterateable {
	private int mCount;
	private int mCurrentIdx;
	private ListItem mFirst;
	private ListItem mLast;

	public void LinkedList() {
		mCount = 0;
		mCurrentIdx = -1;
	}

	public Object at(int index) const {
		if ( index < 0 || index >= mCount ) {
			throw new System.OutOfBoundsException("index " + index + " out of bounds");
		}

		ListItem item = mFirst;
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

	public void next() modify {
		mCurrentIdx++;
	}

	public void push(Object value ref) modify {
		ListItem item = new ListItem();
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

