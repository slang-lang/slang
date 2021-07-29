
// Library imports
import System.CharacterIterator;

// Project imports


public namespace Utils {

public string prettify( string name ) const {
	var it = new CharacterIterator( name );

	string char;
	string result;
	bool upperCase = true;

	while ( it.hasNext() && ( char = it.next() ) ) {
		if ( char == "_" ) {
			upperCase = true;
			continue;
		}

		if ( upperCase ) {
			char = toUpper( char );
			upperCase = false;
		}

		result += char;
	}

	return result;
}

}

