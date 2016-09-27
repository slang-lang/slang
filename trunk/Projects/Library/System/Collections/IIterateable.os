
public namespace System {

	public object Iterator;
	public object ReverseIterator;

	public interface IIterateable {
		public System.Iterator getIterator() const;
	}

	public interface IReverseIterateable {
		public System.ReverseIterator getReverseIterator() const;
	}

}

