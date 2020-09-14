
import System.Exception;
import CollectionItem;
import ICollection;
import Iterator;
import List;
import Pair;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Map<K, V> implements ICollection {
	public void Constructor() {
		mItems = new List<Object>();
	}

	public void Destructor() {
		clear();
	}

	public Map<K, V> Copy() const {
		var result = new Map<K, V>();

		result.mItems = mItems;

		return result;
	}

	public void clear() modify {
		mItems.clear();
	}

	public bool contains( K key ) const {
		foreach ( Object p : mItems ) {
			if ( ( Pair<K, V> p ) == key ) {
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

	public V get( K key ) const throws {
		foreach ( Object p : mItems ) {
			if ( ( Pair<K, V> p ) == key ) {
				return ( Pair<K, V> p ).second;
			}
		}

		throw new Exception( "unknown key!" );
	}

	public Iterator<Object> getIterator() const {
		return new Iterator<Object>( cast<ICollection>( mItems ) );
	}

	public ReverseIterator<Object> getReverseIterator() const {
		return new ReverseIterator<Object>( cast<ICollection>( mItems ) );
	}

	public int indexOf( K key ) const throws {
		int count = 0;

		foreach ( Object p : mItems ) {
			if ( ( Pair<K, V> p ) == key ) {
				return count;
			}
		}

		return -1;
	}

	public void insert( K k, V v ) modify {
		mItems.push_back( cast<Object>( new Pair<K, V>( k, v ) ) );
	}

	public V last() const throws {
		return V mItems.last();
	}

	public void put( K key, V value ) modify throws {
		foreach ( Object p : mItems ) {
			if ( ( Pair<K, V> p ) == key ) {
				var pair = Pair<K, V> p;
				pair.second = value;

				return;
			}
		}

		throw new Exception( "unknown key!" );
	}

	public void remove( K key ) modify {
		int index = 0;

		foreach ( Object p : mItems ) {
			if ( ( Pair<K, V> p ) == key ) {
				mItems.erase( index );
				return;
			}

			index++;
		}
	}

	public int size() const {
		return mItems.size();
	}

	public V operator[]( K key ) const throws {
		return get( key );
	}

	private List<Object> mItems;		// a list of Pair<K, V>

	private Iterator<Object> __iterator;				// this is a hack to automatically initialize a generic type
	private ReverseIterator<Object> __reverse_iterator;		// this is a hack to automatically initialize a generic type
}

