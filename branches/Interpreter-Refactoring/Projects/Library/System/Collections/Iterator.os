
import AbstractCollection;
import System.Exception;

public namespace System {

	public object Iterator {
		private System.AbstractCollection mCollection;
		private int mCurrentIndex;

		public void Constructor(System.AbstractCollection collection ref) {
			mCollection = collection;

			reset();
		}

		public Object current() const {
			if ( !mCollection ) {
				throw new Exception("invalid iterator access");
			}

			return mCollection.at(mCurrentIndex);
		}

		public bool hasNext() const {
			if ( !mCollection ) {
				throw new Exception("invalid iterator access");
			}

			return mCurrentIndex < mCollection.size() - 1;
		}

		public void next() modify {
			if ( !hasNext() ) {
				throw new OutOfBoundsException("index out of bounds");
			}

			mCurrentIndex++;
		}

		public void reset() modify {
			mCurrentIndex = -1;
		}

		public Object =operator(Object none ref) const {
			return current();
		}
	}

	public object ReverseIterator {
		private System.AbstractCollection mCollection;
		private int mCurrentIndex;

		public void Constructor(System.AbstractCollection collection ref) {
			mCollection = collection;

			reset();
		}

		public Object current() const {
			if ( !mCollection ) {
				throw new Exception("invalid iterator access");
			}

			return mCollection.at(mCurrentIndex);
		}

		public bool hasNext() const {
			if ( !mCollection ) {
				throw new Exception("invalid iterator access");
			}

			return mCurrentIndex > 0;
		}

		public void next() modify {
			if ( !hasNext() ) {
				throw new OutOfBoundsException("index out of bounds");
			}

			mCurrentIndex--;
		}

		public void reset() modify {
			mCurrentIndex = mCollection.size();
		}

		public Object =operator(Object none ref) const {
			return current();
		}
	}

}

