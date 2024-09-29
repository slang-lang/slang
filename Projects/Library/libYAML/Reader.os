
// library imports
import System.String;

// project imports
import YamlNode;


public object YamlReader {
	public void Constructor() {
		// nothing to do here
	}

	public YamlNode parse( string text ) throws {
		var lines = new String( text ).SplitBy( LINEBREAK );

		// look for "---" to start parsing
		while ( lines.hasNext() && lines.next() != "---" );

		var result = new YamlNode();

		// do the actual YAML parsing after we found our start token ("---")
		var count = 0;
		while ( lines.hasNext() ) {
			var line = lines.next();

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

			// count indentation
			while( substr( line, indentation++, 1 ) == " " );

			// demo output
			print( cast<string>( count++ ) + ": " + substr( line, indentation ) );

			//indentation /= 2;

			//result.add( new YamlNode( substr( line, indentation ) ) );
		}

		return result;
	}
}

