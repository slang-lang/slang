

/*
 * Double linked collection item
 */
private object CollectionItem {
	public CollectionItem mNext;
	public CollectionItem mPrevious;
	public Object mValue;

	public void Constructor() {
		// this is empty by intend
	}

	public void Constructor(Object value) {
		mValue = value;
	}

	public void Destructor() {
		// this is empty by intend
	}

	public Object get() const {
		return mValue;
	}

	public CollectionItem next() const {
		return mNext;
	}

	public CollectionItem previous() const {
		return mPrevious;
	}

	public void set(Object value) modify {
		mValue = value;
	}
}
