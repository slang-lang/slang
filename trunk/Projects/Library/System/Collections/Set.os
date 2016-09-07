
import ACollection;
import System.Exception;

public namespace System {

	public object Set extends ACollection {
		public void Set() {
			base.ACollection();
		}

		public void insert(Object value) modify {
			if ( !value ) {
				throw new System.Exception("invalid value provided");
			}

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

