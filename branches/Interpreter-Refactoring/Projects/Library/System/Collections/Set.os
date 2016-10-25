
import AbstractCollection;
import System.Exception;

public namespace System {

	public object Set extends System.AbstractCollection {
		public void Constructor() {
			base.Constructor();
		}

		public void erase(int index) modify {
			if ( index < 0 || index > mSize ) {
				throw new OutOfBoundsException("erase index(" + index + ") beyond end of list");
			}

			if ( index == 0 ) {				// special handling for 1st element
				mFirst = mFirst.mNext;
			}
			else {						// default handling for erasing
				CollectionItem prev = mFirst;
				for ( int i = 0; i < index - 1; i = i++ ) {
					prev = prev.mNext;
				}

				if ( index == mSize - 1 ) {
					mLast = prev;
				}
				else if ( prev.mNext ) {
					prev.mNext = prev.mNext.mNext;
				}
			}

			mSize--;
		}

		public void insert(Object value ref) modify {
			CollectionItem item = new CollectionItem(value);

			if ( !mFirst ) {				// special handling for 1st element
				mFirst = item;
				mLast = item;
			}
			else if ( value < mFirst.mValue ) {		// special handling for inserting in 1st position
				item.mNext = mFirst;
				mFirst = item;
			}
			else {						// default handling for insertions
				CollectionItem tmp = mFirst;
				CollectionItem previous;

				for ( int i = 0; i < mSize; i = i++ ) {
					if ( value < tmp.mValue ) {
						break;
					}

					previous = tmp;
					tmp = tmp.mNext;
				}

				item.mNext = previous.mNext;
				previous.mNext = item;
			}

			mSize++;
		}
	}

}

