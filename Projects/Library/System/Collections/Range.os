
import System.Exception;
import ICollection;
import IIterateable;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Range implements ICollection, IIterateable {
/*
	public Range Create(int start, int end, int step = 1) static {
		return new Range(start, end, step);
	}
*/

	public void Constructor(int start, int end, int step = 1) throws {
		if ( !step ) {
			throw new InvalidArgumentException("invalid step size provided!");
		}

		mEnd = end;
		mStart = start;
		mStep = step;
	}

	public int at(int index) const throws {
		if ( index < 0 || index * mStep > mEnd - mStart ) {
			throw new OutOfBoundsException("index (" + index + ") is out of bounds");
		}

		return mStart + index * mStep;
	}

	public int getEnd() const {
		return mEnd;
	}

	public Iterator<int> getIterator() const {
		return new Iterator<int>(ICollection this);
	}

	public int getStart() const {
		return mStart;
	}

	public int getStep() const {
		return mStep;
	}

	public int size() const {
		return (mEnd - mStart) / mStep + 1;
	}

	public int operator[](int index) const throws {
		return at(index);
	}

	private int mEnd const;
	private int mStart const;
	private int mStep const;
}


