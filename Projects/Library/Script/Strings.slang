
// library imports
import System.Collections.Vector;

// project imports


public object Line extends Vector<string> implements IIterable {
    public void Constructor() {
        base.Constructor();
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

