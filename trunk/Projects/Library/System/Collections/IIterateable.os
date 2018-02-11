
import Iterator;

public namespace System.Collections { }

public stable interface IIterateable {
	public Iterator getIterator() const;
}

public stable interface IReverseIterateable {
	public ReverseIterator getReverseIterator() const;
}

