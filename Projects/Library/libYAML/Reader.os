
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

		// do the actual YAML parsing after we found our start token ("---")
		var count = 0;
		while ( lines.hasNext() ) {
			var line = lines.next();

			if ( line && substr( line, 1, 1 ) == "#" ) {
				write( "Comment: " );
				continue;
			}

			print( cast<string>( count++ ) + ": " + line );
		}

		return YamlNode null;
	}
}

