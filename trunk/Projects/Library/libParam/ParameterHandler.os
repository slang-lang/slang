
// Library imports
import System.Collections.IIterateable;
import System.Collections.List;
import System.Exception;
import System.String;

// Project imports


public object Parameter {
	public string FullValue;
	public string Key;
	public string Value;

	public void Constructor(string fullValue) {
		FullValue = fullValue;
		Value = fullValue;
	}

	public void Constructor(string key, string value, string fullValue) {
		FullValue = fullValue;
		Key = key;
		Value = value;
	}

	public string =operator(string) const {
		return Key ? Value : FullValue;
	}
}

public object ParameterHandler implements IIterateable {
	public void Constructor(int argc, string args) {
		mArgc = argc;
		mArgs = args;
		mParameters = new List<Parameter>();

		process();
	}

	public Parameter at(int index) const throws {
		if ( index < 0 || index >= mParameters.size() ) {
			throw new OutOfBoundsException(string index);
		}

		return mParameters.at(index);
	}

	public string stringAt(int index) const throws {
		if ( mParameters.size() <= index ) {
			throw new OutOfBoundsException(string index);
		}

		return string mParameters.at(index);
	}

	public bool empty() const {
		return mParameters.empty();
	}

	public ParameterIterator getIterator() const {
		return new ParameterIterator(this);
	}

	public int size() const {
		return mParameters.size();
	}

	private void process() modify {
		StringIterator it = new StringIterator(mArgs, ascii(10));
		while ( it.hasNext() ) {
			string current = it.next();

			mParameters.push_back(new Parameter(current));
		}

		// verify that we correctly parsed all arguments
		assert( mArgc == mParameters.size() );
	}

	private int mArgc;
	private string mArgs;
	private List<Parameter> mParameters;
}

public object ParameterIterator {
	public void Constructor(ParameterHandler handler ref) {
		mHandler = handler;

		reset();
	}

	public Parameter current() const throws {
		return mHandler.at(mCurrentIndex);
	}

	public bool hasNext() const {
		return mCurrentIndex < mHandler.size() - 1;
	}

	public Parameter next() modify throws {
		mCurrentIndex++;

		return current();
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	private int mCurrentIndex;
	private ParameterHandler mHandler;
}


