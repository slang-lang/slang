
import AbstractCollection;

public namespace System {

	public object StackIterator extends System.Iterator {
		public void StackIterator(System.Stack stack) {
			mCollection = stack;
		}
	}

	public object Stack extends System.AbstractCollection {
			public Iterator getIterator() const {
				// TODO: why do we have to cast here?
				return new Iterator(AbstractCollection this);
			}

			public void push(Object value ref) modify {
				CollectionItem item = new CollectionItem();
				item.mValue = value;

				if ( mSize == 0 ) {		// special handling for 1st item
					mFirst = item;
				}
				else {					// generic handling
					mLast.mNext = item;
				}

				mLast = item;

				mSize++;
			}

			public void pop() modify {
				if ( mSize <= 0 ) {
					throw new OutOfBoundsException("cannot pop beyond ground level");
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
	}

}
