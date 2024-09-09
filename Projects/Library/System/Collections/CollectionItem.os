
// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

/*
 * Double linked collection item
 */
private object CollectionItem<T> {
	public CollectionItem<T> next;
	public CollectionItem<T> previous;
	public T value;

	public void Constructor() {
		// this is empty by intend
	}

	public void Constructor( T v ) {
		value = v;
	}

	public void Destructor() {
		// this is empty by intend
	}

	public CollectionItem<T> Copy() const {
		var result = new CollectionItem<T>();

		result.next = next;
		result.previous = previous;
		result.value = value;

		return result;
	}

	public T get() const {
		return value;
	}

	public CollectionItem<T> next() const {
		return next;
	}

	public void next( CollectionItem<T> n ) modify {
		next = n;
	}

	public CollectionItem<T> previous() const {
		return previous;
	}

	public void previous( CollectionItem<T> p ) modify {
		previous = p;
	}

	public void set( T v ) modify {
		value = v;
	}
}
