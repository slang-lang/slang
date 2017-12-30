
import System.Collections.CollectionItem;
import System.Collections.ICollection;
import System.Collections.Iterator;
import System.Exception;
import Pair;
import Set;

public object MapIterator<K, V> implements Iterator {
	private ICollection mCollection;
	private int mCurrentIndex;

	public void Constructor(ICollection collection ref) {
		mCollection = collection;
	}

	public V at(K index) const {
		return V mCollection[index];
	}

	public V current() const throws {
		if ( !mCollection ) {
			throw new Exception("current(): invalid iterator access");
		}

		return V mCollection.at(mCurrentIndex);
	}

	public bool hasNext() const throws {
		if ( !mCollection ) {
			throw new Exception("hasNext(): invalid iterator access");
		}

		return mCurrentIndex < mCollection.size() - 1;
	}

	public V next() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("next(): index out of bounds");
		}

		mCurrentIndex++;

		return V mCollection.at(mCurrentIndex);
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	public void operator++() modify throws {
		if ( !hasNext() ) {
			throw new OutOfBoundsException("operator++(): index out of bounds");
		}

		mCurrentIndex++;		
	}

	public V =operator(V none ref) const {
		return current();
	}
}

public object Map<K, V> implements ICollection {
	private Set<Object> mItems;		// a set of Pair<K, V>

	public void Constructor() {
		mItems = new Set<Object>();
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

	public V first() const throws {
		return V mItems.first();
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

	public V last() const throws {
		return V mItems.last();
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

