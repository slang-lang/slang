
public namespace System {

	public object Iterator;
	public object ReverseIterator;

	public interface IIterateable {
		public System.Iterator getIterator() const;
	}

	public interface IReverseIterateable {
		public System.ReverseIterator getReverseIterator() const;
	}

	public interface IGenericIterateable<T> implements IIterateable {
		public System.Iterator<T> getIterator() const;
	}

	public interface IGenericReverseIterateable<T> implements IReverseIterateable {
		public System.ReverseIterator<T> getIterator() const;
	}
}

