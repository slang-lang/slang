
// Library imports
import System.Collections.Map;
import System.IO.File;

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
		var file = new System.IO.File( CONFIG_DIRECTORY + "DataTypes.txt" );

		string char;
		string text;
        while ( !file.isEOF() ) {
			char = file.readChar();

			if ( char == " " || char == "	" ) {
				continue;
			}
			else if ( char == LINEBREAK ) {
				insertPair( text );

				text = "";
				continue;
			}

            text += char;
		}
	}

	private Map</*source*/ string, /*target*/ string> mDataTypes;
}

