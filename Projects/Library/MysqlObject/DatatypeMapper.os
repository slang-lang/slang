
// Library imports
import System.Collections.Map;

// Project imports
import Consts;
import Scanner;


public object DatatypeMapper {
	public void Constructor() {
		mDataTypes = new Map<string, string>();

		load();
	}

	public void addType( string left, string right ) modify {
		mDataTypes.insert( left, right );
	}

	public string lookupType( string type ) const throws {
		foreach ( Pair<string, string> p : mDataTypes ) {
			if ( p.first == type ) {
				return p.second;
			}
		}

		throw new Exception( "Type '" + type + "' not found!" );
	}

	private void insertPair( string line ) modify throws {
		var it = new String( line ).SplitBy( ":" );

		mDataTypes.insert( it.next(), it.next() );
	}

	private void load() modify {
		var charIt = new Scanner( CONFIG_DIRECTORY + "DataTypes.txt" ).getIterator();

		string c;
		string text;
		while ( charIt.hasNext() ) {
			c = charIt.next();

			if ( c == " " || c == "	" ) {
				continue;
			}
			else if ( c == LINEBREAK ) {
				insertPair( text );

				text = "";
				continue;
			}

			text += c;
		}
	}

	private Map</*source*/ string, /*target*/ string> mDataTypes;
}

