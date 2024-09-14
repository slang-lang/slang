
import System.Exception;
import ICollection;
import Iterator;
import List;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Queue<T> implements ICollection {
	public void Constructor() {
		mItems = new List<T>();
	}

	public void Destructor() {
		clear();
	}

	public Queue<T> Copy() const {
		var result = new Queue<T>();

		result.mItems = mItems;

		return result;
	}

	public T at( int index ) const throws {
		return mItems.at( index );
	}

	public void clear() modify {
		mItems.clear();
	}

	public T dequeue() modify throws {
		if ( mItems.size() <= 0 ) {
			throw new OutOfBoundsException( "empty collection" );
		}

		var item = mItems.at( 0 );

		mItems.pop_front();

		return item;
	}

	public bool empty() const {
		return mItems.empty();
	}

	public void enqueue( T item ) modify {
		mItems.push_back( item );
	}


///* activate for double linked iterator usage
	public Iterator<T> getIterator() const {
		return mItems.getIterator();
	}

	public ReverseIterator<T> getReverseIterator() const {
		return mItems.getReverseIterator();
	}
//*/

/* activate for random access iterator usage
	public Iterator<Object> getIterator() const {
		return mItems.getIterator();
	}

	public ReverseIterator<Object> getReverseIterator() const {
	return mItems.getReverseIterator();
}
*/

	public T peek() const {
		return mItems.last();
	}

	public int size() const {
		return mItems.size();
	}

	public T operator[]( int index ) const throws {
		return mItems.at( index );
	}

	private List<T> mItems;

	private Iterator<T> __iterator;					// this is a hack to automatically initialize a generic type
	private ReverseIterator<T> __reverse_iterator;	// this is a hack to automatically initialize a generic type
}

