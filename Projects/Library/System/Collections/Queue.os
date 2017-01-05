
import List;
import IIterateable;

public object Queue<T: Object> implements IIterateable {
	private List mItems;

	public void Constructor() {
		mItems = new List();
	}
	public void Destructor() {
		clear();
	}

	public void clear() {
		mItems.clear();
	}

	public T dequeue() modify {
		T item = mItems.at(0);

		mItems.pop_front();

		return item;
	}

	public bool empty() const {
		return mItems.empty();
	}

	public void enqueue(T item) modify {
		mItems.push_back(Object item);
	}

	public Iterator getIterator() const {
		return mItems.getIterator();
	}

	public T peek() const {
		return T mItems.last();
	}

	public int size() const {
		return mItems.size();
	}
}

