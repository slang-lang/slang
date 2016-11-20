
import IIterateable;

public namespace System { }

public interface IGenericCollection implements System.IIterateable {
    public Object at(int index) const;
}
