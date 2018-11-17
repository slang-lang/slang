
// Library imports
import System.Collections.IIterateable;
import System.Collections.List;
import System.Exception;
import System.StringIterator;

// Project imports


public object Parameter {
/*
 * Public
 */

	public string FullValue;
	public string Key;
	public string Value;

	public void Constructor(string fullValue) {
		FullValue = fullValue;
		Key = fullValue;
		Value = fullValue;
	}

	public void Constructor(string key, string value, string fullValue) {
		FullValue = fullValue;
		Key = key;
		Value = value;
	}

	public bool operator==(string key) const {
		return Key == key;
	}

	public string =operator(string) const {
		return Value;
	}
}

public object ParameterHandler implements IIterateable {
/*
 * Public
 */

	public void Constructor(int argc, string args, bool skipProgramName = false) {
		mArgc = argc;
		mArgs = args;
		mParameters = new List<Parameter>();

		process();

		if ( skipProgramName && mParameters.size() > 0 ) {
			// remove first parameter
			mParameters.erase(0);
		}
	}

	public Parameter at(int index) const throws {
		if ( index < 0 || index >= mParameters.size() ) {
			throw new OutOfBoundsException("Index (" + index + ") out of bounds");
		}

		return mParameters.at(index);
	}

	public bool contains(string key) const {
		foreach ( Parameter p : mParameters ) {
			if ( p == key ) {
				return true;
			}
		}

		return false;
	}

	public bool empty() const {
		return mParameters.empty();
	}

	public Iterator<Parameter> getIterator() const {
		return mParameters.getIterator();
	}

	public Parameter getParameter(string key) const throws {
		foreach ( Parameter p : mParameters ) {
			if ( p == key ) {
				return p;
			}
		}

		throw new Exception("key('" + key + "') not found!");
	}

	public int size() const {
		return mParameters.size();
	}

/*
 * Private
 */

	private void process() modify {
		StringIterator it = new StringIterator(mArgs, LINEBREAK);

		while ( it.hasNext() ) {
			string current = it.next();
			int keyPos = 0;
			int startPos = 0;

			if ( substr(current, 0, 1) == "-" ) {
				startPos = 1;

				if ( substr(current, 1, 1) == "-" ) {
					startPos = 2;
				}
			}

			if ( (keyPos = strfind(current, "=")) > 0 ) {
				// extract key, value
				mParameters.push_back(new Parameter(substr(current, startPos, keyPos - startPos), substr(current, keyPos + 1, strlen(current)), current));
				continue;
			}

			mParameters.push_back(new Parameter(substr(current, startPos)));
		}

		// verify that we correctly parsed all arguments
		assert( mArgc == mParameters.size() );
	}

	private int mArgc;
	private string mArgs;
	private List<Parameter> mParameters;
}

