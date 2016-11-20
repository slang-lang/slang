
import AbstractCollection;
import System.Exception;

public namespace System {

	public object GenericIterator<T: Object> {
		private IGenericCollection mCollection;
		private int mCurrentIndex;

		public void Constructor(IGenericCollection collection) {
			mCollection = collection;

			reset();
		}

		public T current() const {
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

		public T next() modify {
			if ( !hasNext() ) {
				throw new OutOfBoundsException("index out of bounds");
			}

			mCurrentIndex++;

			return mCollection.at(mCurrentIndex);
		}

		public void reset() modify {
			mCurrentIndex = -1;
		}

		public T =operator(T none) const {
			return current();
		}
	}

	public object GenericReverseIterator<T> {
		private IGenericCollection mCollection;
		private int mCurrentIndex;

		public void Constructor(IGenericCollection collection) {
			mCollection = collection;

			reset();
		}

		public T current() const {
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

		public T next() modify {
			if ( !hasNext() ) {
				throw new OutOfBoundsException("index out of bounds");
			}

			mCurrentIndex--;

			return mCollection.at(mCurrentIndex);
		}

		public void reset() modify {
			mCurrentIndex = mCollection.size();
		}

		public T =operator(T none) const {
			return current();
		}
	}

}
