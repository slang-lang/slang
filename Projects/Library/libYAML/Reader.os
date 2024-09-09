
import YamlNode;


public object YamlReader {
	public void Constructor() {
		// nothing to do here
	}

	public YamlNode parse( StringIterator lines ) throws {
		var count = 0;
		while ( lines.hasNext() ) {
			var line = lines.next();

			switch ( true ) {
				case line && substr( line, 1, 1 ) == "#" : {
					write( "Comment: " );
					break;
				}
			}

			print( cast<string>( count++ ) + ": " + line );
		}

		return YamlNode null;
	}
}

