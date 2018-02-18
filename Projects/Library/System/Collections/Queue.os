
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;
import List;

public namespace System.Collections { }

public object Queue<T> implements ICollection {
	private List<T> mItems;

	public void Constructor() {
		mItems = new List<T>();
	}

	public void Destructor() {
		clear();
	}

	public void clear() modify {
		mItems.clear();
	}

	public T dequeue() modify throws {
		if ( mItems.size() <= 0 ) {
			throw new OutOfBoundsException("empty collection");
		}

		T item = mItems.at(0);

		mItems.pop_front();

		return item;
	}

	public bool empty() const {
		return mItems.empty();
	}

	public void enqueue(T item) modify {
		mItems.push_back(item);
	}

	public Iterator getIterator() const {
		return mItems.getIterator();
	}

	public T peek() const {
		return mItems.last();
	}

	public int size() const {
		return mItems.size();
	}
}

