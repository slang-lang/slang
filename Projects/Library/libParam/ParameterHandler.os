
// Library imports
import System.CharacterIterator;
import System.Collections.List;
import System.Exception;

// Project imports


public object Parameter {
/*
 * Public
 */

	public string Key;
	public string Value;

	public void Constructor(string key, string value) {
		Key = key;
		Value = value;
	}

	public bool operator==(string key) const {
		return Key == key;
	}

	public string =operator(string) const {
		return Value;
	}

	public string toString() const {
		return "Key: '" + Key + "', Value: '" + Value + "'";
	}
}

public object ParameterHandler implements IIterateable {
/*
 * Public
 */

	public void Constructor(int argc, string args, bool skipProgramName = true) {
		mParameters = new List<Parameter>();

		process(args);

		if ( skipProgramName && mParameters.size() > 0 ) {
			argc--;
			// remove first parameter
			mParameters.erase(0);
		}

		// verify that we correctly parsed all arguments
		assert( argc == mParameters.size() );
	}

	public Parameter at(int index) const throws {
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

	public bool remove(string key) modify throws {
		int idx;

		foreach ( Parameter p : mParameters ) {
			if ( p == key ) {
				mParameters.erase( idx );
				return true;
			}

			idx++;
		}

		return false;
	}

	public int size() const {
		return mParameters.size();
	}

/*
 * Private
 */
	private void insertParameter(string key, string value) modify {
		int startPos;

		if ( substr(key, 0, 1) == "-" ) {
			startPos = 1;
			if ( substr(key, 0, 2) == "--" ) {
				startPos = 2;
			}
		}

		mParameters.push_back(new Parameter(substr(key, startPos), value));
	}

	private void process(string args) modify {
		bool isEscape;
		bool isString;
		bool isValue;
		string key;
		string param;

		var it = new CharacterIterator(args);

		string c;
		while ( it.hasNext() ) {
			c = it.next();

			switch ( true ) {
				case !isEscape && c == "\"": {
					isString = !isString;
					break;
				}
				case !isEscape && c == "\\": {
					isEscape = !isEscape;
					break;
				}
				case !isString && (c == " " || c == LINEBREAK): {
					if ( param || isValue ) {
						insertParameter(isValue ? key : param, isValue ? param : "");
					}

					isEscape = false;
					isString = false;
					isValue = false;
					key = "";
					param = "";
					break;
				}
				case !isString && c == "=": {
					isValue = true;

					key = param;
					param = "";
					break;
				}
				default: {
					isEscape = false;
					param += c;
					break;
				}
			}
		}

		insertParameter(isValue ? key : param, isValue ? param : "");
	}

	private List<Parameter> mParameters;
}

