
import ICollection;
import Pair;
import Set;

public object Map<K, V> implements ICollection {
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
				Pair<K, V> pair = Pair<K, V> p;
				return pair.second;
			}
		}

		throw new Exception("unknown key!");
	}

	public Iterator getIterator() const {
		return new Iterator(ICollection mItems);
	}

	public ReverseIterator getReverseIterator() const {
		return new ReverseIterator(ICollection mItems);
	}

	public void insert(K k, V v) modify {
		mItems.insert(
			Object new Pair<K, V>(k, v)
		);
	}

	public void put(K key, V value) modify throws {
		foreach ( Object p : mItems ) {
			if ( p == key ) {
				Pair<K, V> pair = Pair<K, V> p;
				pair.second = value;
				return;
			}
		}

		throw new Exception("unknown key!");
	}

	public void remove(K key) modify {
		int index = 0;

		foreach ( Object p : mItems ) {
			if ( p == key ) {
				mItems.erase(index);
				return;
			}

			index++;
		}
	}

	public int size() const {
		return mItems.size();
	}

	public V operator[](K key) const {
		return get(key);
	}
}

