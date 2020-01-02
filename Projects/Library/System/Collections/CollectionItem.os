
// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

/*
 * Double linked collection item
 */
private object CollectionItem<T> {
	public CollectionItem<T> mNext;
	public CollectionItem<T> mPrevious;
	public T mValue;

	public void Constructor() {
		// this is empty by intend
	}

	public void Constructor(T value) {
		mValue = value;
	}

	public void Destructor() {
		// this is empty by intend
	}

	public CollectionItem<T> Copy() const {
		CollectionItem<T> result = new CollectionItem<T>();

		result.mNext = mNext;
		result.mPrevious = mPrevious;
		result.mValue = mValue;

		return result;
	}

	public T get() const {
		return mValue;
	}

	public CollectionItem<T> next() const {
		return mNext;
	}

	public void next(CollectionItem<T> n) modify {
		mNext = n;
	}

	public CollectionItem<T> previous() const {
		return mPrevious;
	}

	public void previous(CollectionItem<T> p) modify {
		mPrevious = p;
	}

	public void set(T value) modify {
		mValue = value;
	}
}
