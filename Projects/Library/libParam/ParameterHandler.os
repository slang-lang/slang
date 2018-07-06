
// Library imports
import System.Collections.IIterateable;
import System.Collections.List;
import System.Exception;
import System.String;

// Project imports


public object ParameterHandler implements IIterateable {
	private int mArgc;
	private string mArgs;
	private List<String> mParams;

	public void Constructor(int argc, string args) {
		mArgc = argc;
		mArgs = args;
		mParams = new List<String>();

		process();
	}

	public string at(int index) const throws {
		if ( mParams.size() <= index ) {
			throw new OutOfBoundsException(string index);
		}

		return string mParams.at(index);
	}

	public bool empty() const {
		return mParams.empty();
	}

	public ParameterIterator getIterator() const {
		return new ParameterIterator(this);
	}

	public int size() const {
		return mParams.size();
	}

	private void process() modify {
		StringIterator it = new StringIterator(mArgs, ascii(10));
		while ( it.hasNext() ) {
			mParams.push_back(new String(it.next()));
		}

		// verify that we correctly parsed all arguments
		assert( mArgc == mParams.size() );
	}
}

public object ParameterIterator {
	public void Constructor(ParameterHandler handler) {
		mHandler = handler;

		reset();
	}

	public string current() const throws {
		return mHandler.at(mCurrentPosition);
	}

	public bool hasNext() const {
		return mCurrentPosition <= mHandler.size();
	}

	public string next() modify throws {
		mCurrentPosition++;

		return current();
	}

	public void reset() modify {
		mCurrentPosition = 0;
	}

	private int mCurrentPosition;
	private ParameterHandler mHandler;
}


