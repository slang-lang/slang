
import IIterateable;

public namespace System {

    public interface IGenericCollection<T> implements System.IIterateable {
        public T at(int index) const;
    }

}
