

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

	public T get() const {
		return mValue;
	}

	public CollectionItem<T> next() const {
		return mNext;
	}

	public CollectionItem<T> previous() const {
		return mPrevious;
	}

	public void set(T value) modify {
		mValue = value;
	}
}
