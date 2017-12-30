
import Iterator;

public namespace System.Collections { }

public interface IIterateable {
	public Iterator getIterator() const;
}

public interface IReverseIterateable {
	public ReverseIterator getReverseIterator() const;
}

