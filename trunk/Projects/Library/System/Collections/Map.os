
import IIterateable;
import Pair;
import Set;

public object Map<K, V> implements IIterateable {
	private Set mItems;

	public void Constructor() {
		mItems = new Set();
	}

	public void Destructor() {
		clear();
	}

	public void clear() modify {
		mItems.clear();
	}

	public bool empty() const {
		return mItems.size() == 0;
	}

	public Iterator getIterator() const {
		return new Iterator(AbstractCollection mItems);
	}

	public void insert(K k, V v) modify {
		Pair<K, V> pair = new Pair<K, V>(k, v);

		mItems.insert(Object pair);
	}

	public void remove(K k) modify {
		if ( !mItems.contains(k) ) {
			throw new Exception("unknown key!");
		}


	}

	public int size() const {
		return mItems.size();
	}
}

