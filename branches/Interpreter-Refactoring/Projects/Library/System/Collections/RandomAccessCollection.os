
import AbstractCollection;
import System.Exception;

public namespace System {

	public object RandomAccessCollection extends System.AbstractCollection {
		public void RandomAccessCollection() {
			base.AbstractCollection();
		}

		public void erase(int index) modify {
			if ( index < 0 || index > mSize ) {
				throw new OutOfBoundsException("erase index(" + index + ") beyond end of list");
			}

			if ( index == 0 ) {	            // special handling for 1st element
				mFirst = mFirst.mNext;
			}
			else {	                        // default handling for erasing
				CollectionItem prev = mFirst;
				for ( int i = 0; i < index - 1; i = i++ ) {
					prev = prev.mNext;
				}

				if ( index == mSize - 1 ) {
					mLast = prev;
				}
				else {
					prev.mNext = prev.mNext.mNext;
				}
			}

			mSize--;
		}

		public void insert(Object value ref, int index) modify {
			if ( index < 0 || index > mSize ) {
				throw new OutOfBoundsException("insert index(" + index + ") beyond end of list");
			}

			CollectionItem item = new CollectionItem(value);

			if ( !mFirst ) {
				mFirst = item;
				mLast = item;
			}
			else if ( index == 0 ) {			// special handling for 1st element
				item.mNext = mFirst;
				mFirst = item;
			}
			else if ( index == mSize ) {		// special handling for last element
				mLast.mNext = item;
				mLast = item;
			}
			else {					// default handling for insertions
				CollectionItem tmp = mFirst;
				for ( int i = 0; i < index - 1; i = i++ ) {
					tmp = tmp.mNext;
				}

				item.mNext = tmp.mNext;
				tmp.mNext = item;
			}

			mSize++;
		}
	}

}

