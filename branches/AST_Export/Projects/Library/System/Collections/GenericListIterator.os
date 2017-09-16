
import GenericCollectionItem;

public namespace System.Collections { }

public object GenericIterator<T> {
    private GenericCollectionItem<T> mItem;

    public void Constructor(IGenericCollection<T> collection) {
            if ( !collection ) {
                throw new Exception("invalid collection provided!");
            }

            mItem = collection;
    }

    public void Constructor(GenericCollectionItem<T> item) {
        mItem = item;
    }

    public T =operator(T none) const {
        return mItem.mValue;
    }

    public void operator++() modify {
        if ( !mItem ) {
            throw new Exception("out of bounds");
        }

        mItem = mItem.mNext;
    }

    public void operator--() modify {
        if ( !mItem ) {
            throw new Exception("out of bounds");
        }
        if ( !mItem.mPrevious ) {
            throw new Exception("out of bounds");
        }

        mItem = mItem.mPrevious;
    }
}

