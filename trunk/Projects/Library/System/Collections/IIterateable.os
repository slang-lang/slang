
public namespace System.Collections { }

public object Iterator;
public object ReverseIterator;

public interface IIterateable {
	public Iterator getIterator() const;
}

public interface IReverseIterateable {
	public ReverseIterator getReverseIterator() const;
}

public interface IGenericIterateable<T> implements IIterateable {
	public Iterator<T> getIterator() const;
}

public interface IGenericReverseIterateable<T> implements IReverseIterateable {
	public ReverseIterator<T> getIterator() const;
}

