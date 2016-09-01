
import IIterateable;

public namespace System {

	public object CollectionItem {
			private CollectionItem mNext;
			//private CollectionItem mPrevious;
			private Object mValue;

			public void LinkedItem() {
			}

			public void LinkedItem(Object value ref) {
				mValue = value;
			}

			public Object get() const {
				return mValue;
			}

			public CollectionItem next() const {
				return mNext;
			}

			//public CollectionItem previous() const {
			//	return mPrevious;
			//}

			public void set(Object value ref) modify {
				mValue = value;
			}
	}

	public object ACollection implements IIterateable {
			private int mCurrentIdx;
			private CollectionItem mFirst;
			private CollectionItem mLast;
			private int mSize;

			public void ACollection() {
				mCurrentIdx = -1;
				mSize = 0;
			}

			public Object at(int index) const {
				if ( index < 0 || index >= mSize ) {
					throw new System.OutOfBoundsException("index " + index + " out of bounds");
				}

				CollectionItem item = mFirst;
				for ( int i = 0; i < index; i = i++ ) {
					item = item.mNext;
				}

				return item.mValue;
			}

			public Object current() const {
				return at(mCurrentIdx);
			}

			public bool empty() const {
				return mSize == 0;
			}

			public bool hasNext() const {
				return mCurrentIdx < mSize - 1;
			}

			public void next() modify {
				mCurrentIdx++;
			}

			public void reset() modify {
				mCurrentIdx = -1;
			}

			public int size() const {
				return mSize;
			}
	}

}
