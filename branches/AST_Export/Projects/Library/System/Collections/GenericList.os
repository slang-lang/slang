
import GenericCollectionItem;
import GenericIterator;
import IGenericCollection;
import IIterateable;
import Iterator;
import System.Exception;

public object GenericList<T> implements IGenericIterateable<T>, IGenericCollection<T> {
    private GenericCollectionItem<T> mFirst;
    private GenericCollectionItem<T> mLast;
    private int mSize = 0;

    public void Constructor() {
        // this is empty by intend
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
        mFirst = GenericCollectionItem<T> null;
        mLast = GenericCollectionItem<T> null;
        mSize = 0;
    }

    public bool contains(T value) const {
        GenericCollectionItem<T> tmp = mFirst;

        while ( tmp ) {
            if ( tmp.mValue == value ) {
                return true;
            }

            tmp = tmp.mNext;
        }

        return false;
    }

    public bool empty() const {
        return mSize == 0;
    }

    public GenericIterator<T> find(T value) const {
        GenericCollectionItem<T> tmp = mFirst;

        while ( tmp ) {
            if ( tmp.mValue == value ) {
                return new GenericIterator<T>(tmp);
            }

            tmp = tmp.mNext;
        }

        return null;
    }

    public GenericIterator<T> first() const {
        return new GenericIterator<T>(mFirst);
    }

    public GenericIterator<T> last() const {
        return new GenericIterator<T>(mLast);
    }

    public void pop_back() modify throws {
        if ( mSize <= 0 ) {
            throw new Exception("out of bounds");
        }

        GenericCollectionItem<T> last = mLast;

        GenericCollectionItem<T> tmp = last.mPrevious;
        if ( tmp ) {
            tmp.mNext = null;
        }
        else {
            mFirst = null;
            mLast = null;
        }

        mSize--;
    }

    public int size() const {
        return mSize;
    }

    public void push_back(T value) modify {
        GenericCollectionItem<T> item = new GenericCollectionItem<T>(value);

        item.mPrevious = mLast;

	if ( !mFirst ) {
		mFirst = item;
	}

	GenericCollectionItem<T> tmp = mLast;

	mLast = item;
	mLast.mPrevious = tmp;

        mSize++;
    }
}

