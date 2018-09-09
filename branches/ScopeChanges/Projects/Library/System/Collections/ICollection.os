
import IIterateable;

public namespace System.Collections { }

public stable interface ICollection implements IIterateable, IReverseIterateable {
    public Object at(int index) const throws;
    public int size() const;

    public Object operator[](int index) const throws;
}

