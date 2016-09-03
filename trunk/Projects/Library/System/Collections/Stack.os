
import ACollection;

public namespace System {

	public object Stack extends ACollection {
			public void Stack() {
				base.ACollection();
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
					throw new System.OutOfBoundsException("cannot pop beyond ground level");
				}

				Object null;

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
