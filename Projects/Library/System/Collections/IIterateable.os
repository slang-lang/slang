
import Iterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public stable interface IIterateable {
	public Iterator getIterator() const;
}

public stable interface IReverseIterateable {
	public ReverseIterator getReverseIterator() const;
}

