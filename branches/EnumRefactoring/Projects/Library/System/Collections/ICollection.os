
import IIterateable;

public interface ICollection implements IIterateable, IReverseIterateable {
    public Object at(int index) const throws;
    public int size() const;

    public Object operator[](int index) const throws;
}
