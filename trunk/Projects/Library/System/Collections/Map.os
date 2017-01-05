
import IIterateable;
import Pair;
import Set;

public object Map<K, V> implements IIterateable {
	private Set mItems;		// a set of Pair<K, V>

	public void Constructor() {
		mItems = new Set();
	}

	public void Destructor() {
		clear();
	}

	public void clear() modify {
		mItems.clear();
	}

	public bool contains(K key) const {
		foreach ( Object p : mItems ) {
			if ( p == key ) {
				return true;
			}
		}

		return false;
	}

	public bool empty() const {
		return mItems.size() == 0;
	}

	public V get(K key) const throws {
		foreach ( Object p : mItems ) {
			if ( p == key ) {
				return p.second;
			}
		}

		throw new Exception("unknown key!");
	}

	public Iterator getIterator() const {
		return new Iterator(AbstractCollection mItems);
	}

	public ReverseIterator getReverseIterator() const {
		return new ReverseIterator(AbstractCollection mItems);
	}

	public void insert(K k, V v) modify {
		Pair<K, V> pair = new Pair<K, V>(k, v);

		mItems.insert(Object pair);
	}

	public void put(K key, V value) modify throws {
		foreach ( Object p : mItems ) {
			if ( p == key ) {
				p.second = value;
				return;
			}
		}

		throw new Exception("unknown key!");
	}

	public void remove(K key) modify throws {
		int index = 0;

		foreach ( Object p : mItems ) {
			if ( p == key ) {
				mItems.erase(index);
			}

			index++;
		}
	}

	public int size() const {
		return mItems.size();
	}
}

