
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public stable interface IIterable {
	public Iterator getIterator() const;
}

public stable interface IReverseIterable {
	public ReverseIterator getReverseIterator() const;
}

