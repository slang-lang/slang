
import System.CharacterIterator;


public namespace Utils {

    public string prettify( string name ) const {
        var it = new CharacterIterator( name );

        string result;
        bool upperCase = true;

        while ( it.hasNext() ) {
            string c = it.next();

            if ( c == "_" ) {
                upperCase = true;
                continue;
            }

            if ( upperCase ) {
                c = toUpper( c );
                upperCase = false;
            }

            result += c;
        }

        return result;
    }

}
