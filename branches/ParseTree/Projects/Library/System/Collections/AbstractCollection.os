
import IIterateable;
import Iterator;

public namespace System {

	/*
	 * Double linked collection item
	 */
	public object CollectionItem {
		public System.CollectionItem mNext;
		public System.CollectionItem mPrevious;
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

		public System.CollectionItem next() const {
			return mNext;
		}

		public System.CollectionItem previous() const {
			return mPrevious;
		}

		public void set(Object value ref) modify {
			mValue = value;
		}
	}

	/*
	 * Abstract base for collections
	 */
	public abstract object AbstractCollection implements System.IIterateable {
		protected System.CollectionItem mFirst;
		protected System.CollectionItem mLast;
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

		public System.Iterator getIterator() const {
			// TODO: why do we have to cast here?
			return new Iterator(AbstractCollection this);
		}

		public System.ReverseIterator getReverseIterator() const {
			// TODO: why do we have to cast here?
			return new ReverseIterator(AbstractCollection this);
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
