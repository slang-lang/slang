
import AbstractCollection;
import System.Exception;

public namespace System.Collections { }

public object Set extends AbstractCollection {
	private bool mAllowDuplicates;

	public void Constructor(bool allowDuplicates = false) {
		base.Constructor();

		mAllowDuplicates = allowDuplicates;
	}

	public void erase(int index) modify throws {
		if ( index < 0 || index > mSize ) {
			throw new OutOfBoundsException("erase index(" + index + ") beyond end of list");
		}

		if ( index == 0 ) {						// special handling for 1st element
			mFirst = mFirst.mNext;
		}
		else {									// default handling for erasing
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

			if ( !mAllowDuplicates ) {
				if ( previous.mNext ) {
					if ( item == previous.mNext ) {
						throw Exception("duplicate item");
					}
				}
			}

			item.mNext = previous.mNext;
			previous.mNext = item;
		}

		mSize++;
	}
}

