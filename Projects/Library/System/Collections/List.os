
import ACollection;
import System.Exception;

public namespace System {

    /*
     * Single linked list
     */
    public object List extends ACollection {
        public void List() {
            base.ACollection();
        }

        public void pop_back() modify {
            if ( mSize <= 0 ) {
                throw new System.OutOfBoundsException("cannot pop beyond ground level");
            }

            Object null;

            if ( mSize == 1 ) {
                mFirst = null;
            }
            else {
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
                throw new System.OutOfBoundsException("pop beyond begin of list");
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

}

