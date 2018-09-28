
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;
import List;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Queue<T> implements ICollection {
	public void Constructor() {
		// this determines if we are dealing with an object type or a native data type
		T check;
		mIsObjectType = check is Object;

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

	public Iterator<T> getIterator() const {
		return mItems.getIterator();
	}

	public T peek() const {
		return mItems.last();
	}

	public int size() const {
		return mItems.size();
	}

	private bool mIsObjectType;
	private List<T> mItems;

	private Iterator<T> __iterator;				// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;		// this is a hack to automatically initialize a generic type
}

