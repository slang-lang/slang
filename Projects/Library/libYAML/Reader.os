
// library imports
import System.String;

// project imports
import Array;
import Object;
import Value;


public object YamlReader {
	public YamlValue parse( string text ) throws {
		var lineIt = new String( text ).SplitBy( LINEBREAK );

		// look for "---" to start parsing
		while ( lineIt.hasNext() && lineIt.next() != "---" );

		var root = new YamlObject();

		YamlValue previous;
		int previousIndentation;

		// do the actual YAML parsing after we found our start token ("---")
		var count = 0;
		while ( lineIt.hasNext() ) {
			var line = lineIt.next();

			// ignore invalid lines
			if ( ! line )
				continue;

			// look for document end
			if ( line == "..." )
				break;

			// filter out line comments first
			if ( substr( line, 1, 1 ) == "#" ) {
				write( "Comment: " );
				continue;
			}

			int indentation;

			// demo output
			print( cast<string>( count++ ) + ": " + line );

			// count indentation
			while( substr( line, indentation++, 1 ) == " " );

			line = substr( line, indentation );

			if ( substr( line, 1, 1 ) == "-" )
				line = substr( line, 2 );

			var keyEndPos = strfind( line, ":" );
			var spacePos  = strfind( line, " " );

			string key;
			string value;

			if ( keyEndPos != -1 && keyEndPos < spacePos ) {
				key  = substr( line, 0, keyEndPos );
				line = substr( line, keyEndPos + 2 );
			}
			else if ( spacePos == -1 ) {
				key  = substr( line, 0, keyEndPos );
				line = "";
			}

			value = line;

			print( key + ":" + value );

			// demo output
			//print( cast<string>( count++ ) + ": " + line );

			var current = new YamlValue( value );

			var parent = findParent( root, indentation / 2 );

			parent.addMember( key, current );

			//previous            = current;
			//previousIndentation = indentation;
		}

		return YamlValue root;
	}

	private YamlObject findParent( YamlObject root, int level ) const {
		var obj = root;

		while ( level-- > 0 )
			obj = obj[ obj.size() - 1 ];

		return obj;
	}
}

