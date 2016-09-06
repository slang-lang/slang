
import IIterateable;
import Iterator;

public namespace System {

	/*
	 * Double linked collection item
	 */
	public object CollectionItem {
		private CollectionItem mNext;
		private CollectionItem mPrevious;
		private Object mValue;

		public void CollectionItem() {
		}

		public void CollectionItem(Object value ref) {
			mValue = value;
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
	public object ACollection {
		private CollectionItem mFirst;
		private CollectionItem mLast;
		private int mSize;

		public void ACollection() {
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

		public bool empty() const {
			return mSize == 0;
		}

		public Iterator getIterator() const {
			return new System.Iterator(System.ACollection this);
		}

		public ReverseIterator getReverseIterator() const {
			return new ReverseIterator(System.ACollection this);
		}

		public int size() const {
			return mSize;
		}
	}

}
