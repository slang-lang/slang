
import System.Exception;
import ICollection;
import RandomAccessIterator;

// declare 'System.Collections' namespace to prevent a user defined private 'System' namespace
public namespace System.Collections { }

public object Range implements ICollection, IIterable {

	/*
	 * Range factory method
	 */
	public static Range Create( int _start, int _end, int _step = 1 ) {
		return new Range( _start, _end, _step );
	}

	/*
	 * Default constructor
	 */
	public void Constructor( int _start, int _end, int _step = 1 ) throws {
		if ( !_step ) {
			throw new InvalidArgumentException( "invalid step size provided!" );
		}

		mEnd = _end;
		mStart = _start;
		mStep = _step;
	}

	/*
	 * Copy constructor
	 */
	public Range Copy() const {
		return new Range( mStart, mEnd, mStep );
	}

	public int at( int index ) const throws {
		if ( index < 0 || index * mStep > mEnd - mStart ) {
			throw new OutOfBoundsException( "index (" + index + ") is out of bounds" );
		}

		return mStart + index * mStep;
	}

	public int getEnd() const {
		return mEnd;
	}


///* activate for random access iterator usage
	public RandomAccessIterator<int> getIterator() const {
		return new RandomAccessIterator<int>( ICollection this );
	}

	public ReverseRandomAccessIterator<int> getReverseIterator() const {
		return new ReverseRandomAccessIterator<int>( ICollection this );
	}
//*/

	public int getStart() const {
		return mStart;
	}

	public int getStep() const {
		return mStep;
	}

	/*
	 * returns a new Range object with given step size
	 * throws Exception
	 */
	public Range step( int stepSize ) throws {
		if ( stepSize == 0 ) {
			throw new Exception( "invalid step size(" + stepSize + ") provided" );
		}

		return new Range( mStart, mEnd, stepSize );
	}

	public int getStart() const {
		return mStart;
	}

	public int getStep() const {
		return mStep;
	}

	/*
	 * returns a new Range object with given step size
	 * throws Exception
	 */
	public Range step(int stepSize) throws {
		if ( stepSize == 0 ) {
			throw new Exception("invalid step size(" + stepSize + ") provided");
		}

		return new Range(mStart, mEnd, stepSize);
	}

	public int size() const {
		return ( mEnd - mStart ) / mStep + 1;
	}

	public int operator[]( int index ) const throws {
		return at( index );
	}

	private int mEnd const;
	private int mStart const;
	private int mStep const;

	private RandomAccessIterator<int> __iterator;					// this is a hack to automatically initialize a generic type
	private ReverseRandomAccessIterator<int> __reverse_iterator;	// this is a hack to automatically initialize a generic type
}


