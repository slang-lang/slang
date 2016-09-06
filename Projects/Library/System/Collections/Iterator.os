
import ACollection;
import IIterateable;
import System.Exception;

public namespace System {

	public object Iterator implements IIterateable {
		private System.ACollection mCollection;
		private int mCurrentIndex;

		public void Iterator(System.ACollection collection) {
			mCollection = collection;

			reset();
		}

		public Object current() const {
			if ( !mCollection ) {
				throw new System.Exception("invalid iterator access");
			}

			return mCollection.at(mCurrentIndex);
		}

		public bool hasNext() const {
			if ( !mCollection ) {
				throw new System.Exception("invalid iterator access");
			}

			return mCurrentIndex < mCollection.size() - 1;
		}

		public void next() modify {
			if ( !hasNext() ) {
				throw new System.OutOfBoundsException("index out of bounds");
			}

			mCurrentIndex++;
		}

		public void reset() modify {
			mCurrentIndex = -1;
		}

		public Object =operator(Object value) const {
			return current();
		}
	}

	public object ReverseIterator implements IIterateable {
		private System.ACollection mCollection;
		private int mCurrentIndex;

		public void ReverseIterator(System.ACollection collection) {
			mCollection = collection;

			reset();
		}

		public Object current() const {
			if ( !mCollection ) {
				throw new System.Exception("invalid iterator access");
			}

			return mCollection.at(mCurrentIndex);
		}

		public bool hasNext() const {
			if ( !mCollection ) {
				throw new System.Exception("invalid iterator access");
			}

			return mCurrentIndex > 0;
		}

		public void next() modify {
			if ( !hasNext() ) {
				throw new System.OutOfBoundsException("index out of bounds");
			}

			mCurrentIndex--;
		}

		public void reset() modify {
			mCurrentIndex = mCollection.size();
		}
	}

}

