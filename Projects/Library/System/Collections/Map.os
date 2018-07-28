
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;
import List;
import Pair;

public namespace System.Collections { }

public object Map<K, V> implements ICollection {
	private List<Object> mItems;		// a list of Pair<K, V>

	public void Constructor() {
		mItems = new List<Object>();
	}

	public void Destructor() {
		clear();
	}

	public void clear() modify {
		mItems.clear();
	}

	public bool contains(K key) const {
		foreach ( Object p : mItems ) {
			if ( (Pair<K, V> p) == key ) {
				return true;
			}
		}

		return false;
	}

	public bool empty() const {
		return mItems.size() == 0;
	}

	public V first() const throws {
		return V mItems.first();
	}

	public V get(K key) const throws {
		foreach ( Object p : mItems ) {
			if ( (Pair<K, V> p) == key ) {
				Pair<K, V> pair = Pair<K, V> p;
				return pair.second;
			}
		}

		throw new Exception("unknown key!");
		//throw new Exception("unknown key '" + (string key) + "'!");
	}

	public Iterator<Object> getIterator() const {
		return new Iterator<Object>(ICollection mItems);
	}

	public ReverseIterator<Object> getReverseIterator() const {
		return new ReverseIterator<Object>(ICollection mItems);
	}

	public int indexOf(K key) const throws {
		int count = 0;

		foreach ( Object p : mItems ) {
			if ( (Pair<K, V> p) == key ) {
				return count;
			}
		}

		return -1;
	}

	public void insert(K k, V v) modify {
		mItems.push_back(
			Object new Pair<K, V>(k, v)
		);
	}

	public V last() const throws {
		return V mItems.last();
	}

	public void put(K key, V value) modify throws {
		foreach ( Object p : mItems ) {
			if ( (Pair<K, V> p) == key ) {
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
			if ( (Pair<K, V> p) == key ) {
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

