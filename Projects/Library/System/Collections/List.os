
import AbstractCollection;
import System.Exception;

public namespace System.Collections { }

/*
 * Single linked list
 */
public object List extends AbstractCollection {
    public void Constructor() {
        base.Constructor();
    }

    public void pop_back() modify {
        if ( mSize <= 0 ) {
            throw new OutOfBoundsException("cannot pop beyond ground level");
        }

        if ( mSize == 1 ) {		// special handling for 1st item
            mFirst = null;
        }
        else {					// generic handling
            CollectionItem item = mFirst;
            for ( int i = 0; i < mSize - 1; i = i++ ) {
                item = item.mNext;
            }

            item.mNext = null;
        }

        mSize--;
    }

    public void pop_front() modify {
        if ( mSize <= 0 ) {
            throw new OutOfBoundsException("pop beyond begin of list");
        }

        mFirst = mFirst.mNext;

        mSize--;
    }

    public void push_back(Object value ref) modify {
        CollectionItem item = new CollectionItem();
        item.mValue = value;

        if ( mSize == 0 ) {     // special handling for 1st item
            mFirst = item;
        }
        else {                  // generic handling
            mLast.mNext = item;
        }

        mLast = item;

        mSize++;
    }

    public void push_front(Object value ref) modify {
        CollectionItem item = new CollectionItem(value);

        item.mNext = mFirst;
        mFirst = item;

        mSize++;
    }
}

