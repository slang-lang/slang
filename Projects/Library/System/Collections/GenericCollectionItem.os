
public namespace System.Collections { }

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

    public void operator=(T value) modify {
        mValue = value;
    }
}

