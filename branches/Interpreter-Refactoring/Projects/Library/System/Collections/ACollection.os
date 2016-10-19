
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
		private int mSize = 0;

		public void ACollection() {
			mSize = 0;
		}

		public Object at(int index) const {
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

		public Iterator getIterator() const {
			// TODO: why do we have to cast here?
			return new Iterator(System.ACollection this);
		}

		public ReverseIterator getReverseIterator() const {
			// TODO: why do we have to cast here?
			return new ReverseIterator(System.ACollection this);
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
	}

}
