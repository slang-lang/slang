
import IIterateable;
import System.Exception;

public namespace System {

    public object LinkedItem {
        private LinkedItem mNext;
        private Object mValue;

        public void LinkedItem() {
        }

        public void LinkedItem(Object value ref) {
            mValue = value;
        }

        public Object get() const {
            return mValue;
        }

        public LinkedItem next() const {
            return mNext;
        }

        public void set(Object value ref) modify {
            mValue = value;
        }
    }

    public object LinkedList implements IIterateable {
        private int mCurrentIdx;
        private LinkedItem mFirst;
        private LinkedItem mLast;
        private int mSize;

        public void LinkedList() {
            mCurrentIdx = -1;
            mSize = 0;
        }

        public Object at(int index) const {
            if ( index < 0 || index >= mSize ) {
                throw new System.OutOfBoundsException("index " + index + " out of bounds");
            }

            LinkedItem item = mFirst;
            for ( int i = 0; i < index; i = i++ ) {
                item = item.mNext;
            }

            return item.mValue;
        }

        public Object current() const {
            return at(mCurrentIdx);
        }

        public bool empty() const {
            return mSize == 0;
        }

        public void erase(int index) modify {
            if ( index < 0 || index > mSize ) {
                throw new System.OutOfBoundsException("erase index(" + index + ") beyond end of list");
            }

            if ( index == 0 ) {	            // special handling for 1st element
                mFirst = mFirst.mNext;
            }
            else {	                        // default handling for erasing
                LinkedItem prev = mFirst;
                for ( int i = 0; i < index - 1; i = i++ ) {
                    prev = prev.mNext;
                }

                prev = prev.mNext.mNext;

                if ( index == mSize - 1 ) {
                    mLast = prev;
                }
            }

            mSize--;
        }

        public void insert(Object value ref, int index) modify {
            if ( index > mSize ) {
                throw new System.OutOfBoundsException("insert index(" + index + ") beyond end of list");
            }

            LinkedItem item = new LinkedItem(value);

            if ( index == 0 ) {	            // special handling for 1st element
                item.mNext = mFirst;
                mFirst = item;
                mLast = item;
            }
            else if ( index == mSize ) {   // special handling for last element
                mLast.mNext = item;
                mLast = item;
            }
            else {	                        // default handling for insertions
                LinkedItem tmp = mFirst;
                for ( int i = 0; i < index - 1; i = i++ ) {
                    tmp = tmp.mNext;
                }

                item.mNext = tmp.mNext;
                tmp.mNext = item;
            }

            mSize++;
        }

        public bool hasNext() const {
            return mCurrentIdx < mSize - 1;
        }

        public void next() modify {
            mCurrentIdx++;
        }

        public void push_back(Object value ref) modify {
            LinkedItem item = new LinkedItem();
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
            LinkedItem item = new LinkedItem(value);

            item.mNext = mFirst;
            mFirst = item;

            mSize++;
        }

        public void reset() modify {
            mCurrentIdx = -1;
        }

        public int size() const {
            return mSize;
        }
    }

}

