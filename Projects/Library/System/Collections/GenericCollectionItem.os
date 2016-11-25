
public namespace System { }

public object GenericCollectionItem<T> {
    public GenericCollectionItem<T> mNext;
    public GenericCollectionItem<T> mPrevious;
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

    public GenericCollectionItem<T> next() const {
        return mNext;
    }

    public GenericCollectionItem<T> previous() const {
        return mPrevious;
    }

    public void set(T value) modify {
        mValue = value;
    }
}
