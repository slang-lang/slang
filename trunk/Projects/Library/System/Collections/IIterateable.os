
public namespace System {

	public interface IIterateable {
		public Object current() const;
		public bool hasNext() const;
		public void next() modify;
		public void reset() modify;
	}

	public interface IReverseIterateable implements IIterateable {
		public bool hasPrevious() const;
		public void previous() modify;
	}

}

