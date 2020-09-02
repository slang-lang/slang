
// Library imports
import System.CharacterIterator;
import System.Collections.List;
import System.Exception;

// Project imports


public object Parameter const {
/*
 * Public
 */

	public string Key const;
	public string Value const;

	public void Constructor( string key, string value ) {
		Key = key;
		Value = value;
	}

	public bool operator==( string key ) const {
		return Key == key;
	}

	public string =operator( string ) const {
		return Value;
	}

	public string toString() const {
		return "Parameter { Key: '" + Key + "', Value: '" + Value + "' }";
	}
}


public object ParameterHandler implements IIterable {
/*
 * Public
 */

	public void Constructor( int argc, string args, bool skipProgramName = true ) {
		mParameters = new List<Parameter>();

		process( args );

		if ( skipProgramName && !mParameters.empty() ) {
			argc--;
			// remove first parameter
			mParameters.erase( 0 );
		}

		// verify that we correctly parsed all arguments
		assert( argc == mParameters.size() );
	}

	/*
	 * Subscript operator which retrieves a parameter using its index as lookup
	 */
	public Parameter operator[]( int index ) const throws {
		return mParameters.at( index );
	}

	/*
	 * Subscript operator which retrieves a parameter using its key as lookup
	 */
	public Parameter operator[]( string key ) const throws {
		foreach ( Parameter p : mParameters ) {
			if ( p == key ) {
				return p;
			}
		}

		throw new Exception( "key( '" + key + "' ) not found!" );
	}

	/*
	 * DEPRECATED: retrieves a parameter using its index as lookup
	 */
	public deprecated Parameter at( int index ) const throws {
		return operator[]( index );
	}

	/*
	 * returns true if a parameter with the given key exists
	 */
	public bool contains( string key ) const {
		foreach ( Parameter p : mParameters ) {
			if ( p == key ) {
				return true;
			}
		}

		return false;
	}

	/*
	 * returns true if no parameter is held at all
	 */
	public bool empty() const {
		return mParameters.empty();
	}

	/*
	 * returns an iterator to all the held parameters
	 */
	public Iterator<Parameter> getIterator() const {
		return mParameters.getIterator();
	}

	/*
	 * DEPRECATED: retrieves a parameter using its key as lookup
	 */
	public deprecated Parameter getParameter( string key ) const throws {
		return operator[]( key );
	}

	/*
	 * removes a parameter from the container by checking its key
	 */
	public bool remove( string key ) modify throws {
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

	/*
	 * removes a parameter from the container by checking its reference
	 */
	public bool remove( Parameter param const ) modify throws {
		int idx;

		foreach ( Parameter p : mParameters ) {
			if ( p == param ) {
				mParameters.erase( idx );
				return true;
			}

			idx++;
		}

		return false;
	}

	/*
	 * returns the number of held parameters
	 */
	public int size() const {
		return mParameters.size();
	}

/*
 * Private
 */
	/*
	 * inserts the parsed parameters
	 */
	private void insertParameter( string key, string value ) modify {
		int startPos;

		if ( substr( key, 0, 1 ) == "-" ) {
			startPos = 1;
			if ( substr( key, 0, 2 ) == "--" ) {
				startPos = 2;
			}
		}

		mParameters.push_back( new Parameter( substr( key, startPos ), value ) );
	}

	/*
	 * parses all arguments and inserts parameters for them
	 */
	private void process( string args ) modify {
		bool isEscape;
		bool isString;
		bool isValue;
		string key;
		string param;

		var it = new CharacterIterator( args );

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
				case !isString && ( c == " " || c == LINEBREAK ): {
					if ( param || isValue ) {
						insertParameter( isValue ? key : param, isValue ? param : "" );
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

		insertParameter( isValue ? key : param, isValue ? param : "" );
	}

	private List<Parameter> mParameters;
}

