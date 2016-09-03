
import ACollection;
import System.Exception;

public namespace System {

	/*
	 * Double linked list
	 * allows reverse iteration
	 */
	public object DoubleLinkedList extends ACollection {
		public void DoubleLinkedList() {
			base.ACollection();
		}

		public bool hasPrevious() const {
			return mCurrentIdx > 0;
		}

		public void pop_back() modify {
			if ( mSize <= 0 ) {
				throw new System.OutOfBoundsException("cannot pop beyond ground level");
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

		public void pop_front() modify {
			if ( mSize <= 0 ) {
				throw new System.OutOfBoundsException("pop beyond begin of list");
			}

			mFirst = mFirst.mNext;

			mSize--;
		}

		public void previous() modify {
			mCurrentIdx--;
		}

		public void push_back(Object value ref) modify {
			CollectionItem item = new CollectionItem();
			item.mValue = value;

			if ( mSize == 0 ) {
				mFirst = item;
			}
			else {
				mLast.mNext = item;
			}

			item.mPrevious = mLast;
			mLast = item;

			mSize++;
		}

		public void push_front(Object value ref) modify {
			CollectionItem item = new CollectionItem(value);

			if ( mSize == 0 ) {     // special handling for 1st element
				mFirst = item;
			}
			else {                  // generic handling for all elements
				item.mNext = mFirst;
				mFirst.mPrevious = item;
				mFirst = item;
			}

			mSize++;
		}

		public void resetToLast() modify {
			mCurrentIdx = mSize;
		}
	}

}

