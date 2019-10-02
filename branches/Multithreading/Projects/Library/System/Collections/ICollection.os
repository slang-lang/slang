
import IIterable;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public stable interface ICollection implements IIterable, IReverseIterable {
    public Object at(int index) const throws;
    public int size() const;

    public Object operator[](int index) const throws;
}

