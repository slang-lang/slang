
import GenericCollectionItem;
import IIterateable;
import Iterator;
import System.Exception;

public namespace System { }

public object GenericStack<T> implements IIterateable {
    private GenericCollectionItem<T> mFirst;
    private GenericCollectionItem<T> mLast;
    private int mSize = 0;

    public void Constructor() {
        mSize = 0;
    }
    public void Destructor() {
        clear();
    }

    public T at(int index) const throws {
        if ( index < 0 || index >= mSize ) {
            throw new OutOfBoundsException("index(" + index + ") out of bounds");
        }

        GenericCollectionItem<T> item = mFirst;
        for ( int i = 0; i < index; i = i++ ) {
            item = item.mNext;
        }

        return item.mValue;
    }

    public void clear() modify {
        for ( int i = 0; i < mSize; i = i++ ) {
            mFirst.mValue = null;
            mFirst = mFirst.mNext;
        }

        mSize = 0;
    }

    public bool contains(T value) const {
        return indexOf(value) != -1;
    }

    public bool empty() const {
        return mSize == 0;
    }
/*
    public System.Iterator getIterator() const {
        // TODO: why do we have to cast here?
        return new Iterator(this);
    }

    public System.ReverseIterator getReverseIterator() const {
        // TODO: why do we have to cast here?
        return new ReverseIterator(this);
    }
*/
    public int indexOf(T value) const {
        GenericCollectionItem<T> item = mFirst;
        for ( int i = 0; i < mSize; i = i++ ) {
            if ( item.mValue == value ) {
                return i;
            }

            item = item.mNext;
        }

        return -1;
    }

    public T peek() const {
        if ( mSize <= 0 ) {
            throw new OutOfBoundsException("stack underflow");
        }

        return mLast.mValue;
    }

    public void push(T value) modify {
        GenericCollectionItem<T> item = new GenericCollectionItem<T>(value);

        if ( mSize == 0 ) {		// special handling for 1st item
            print(typeid(item) + " item");
            print(typeid(mFirst) + " mFirst");
            print(typeid(mLast) + " mLast");

            mFirst = item;
        }
        else {					// generic handling
            mLast.mNext = item;
        }

        mLast = item;

        mSize++;
    }

    public void pop() modify {
        if ( mSize <= 0 ) {
            throw new OutOfBoundsException("stack underflow");
        }

        if ( mSize == 1 ) {
            mFirst = null;
        }
        else {
            GenericCollectionItem<T> item = mFirst;
            for ( int i = 0; i < mSize - 1; i = i++ ) {
                item = item.mNext;
            }

            item.mNext = null;

            mLast = item;
        }

        mSize--;
    }

    public int size() const {
        return mSize;
    }
}
