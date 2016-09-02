
import ACollection;
import System.Exception;

public namespace System {

	public object DoubleLinkedList extends ACollection {
		public void DoubleLinkedList() {
			base.ACollection();
		}

		public bool hasPrevious() const {
			return mCurrentIdx > 0;
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

        public void push_front() modify {
        }

		public void resetToLast() modify {
			mCurrentIdx = mSize;
		}
	}

}

