
// library imports
import System.Collections.Vector;

// project imports


public object Row {
    public void Constructor() {
        mEntry = new Vector<string>();
    }

    public void Constructor( Vector<string> data ) {
        mEntry = data;
    }

    public int size() const {
        return mEntry.size();
    }

    public string operator[]( int index ) throws {
        return mEntry.at( index );
    }

    public string operator[]( string column ) throws {
        return mEntry.get( column );
    }

    public string =operator( string ) const {
        string result;

        foreach ( string entry : mEntry ) {
            if ( result ) {
                result += " | ";
            }

            result += entry;
        }

        return result;
    }

    private Vector<string> mEntry;
}
