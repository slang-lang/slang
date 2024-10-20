
// library imports
import System.Collections.Vector;

// project imports


public object Row extends Vector<string> implements IIterable {
    public void Constructor() {
        base.Constructor();
    }

    public int getIdx( string column ) const {
        for ( var idx = 0; idx < size(); idx++ ) {
            if ( at( idx ) == column ) {
                return idx;
            }
        }

        return -1;
    }

    public string =operator( string ) const {
        string result;

        foreach ( string entry : getIterator() ) {
            if ( result ) {
                result += " | ";
            }

            result += entry;
        }

        return result;
    }
}
