
// library imports
import System.Collections.Map;

// project imports


public object DataEntry {
    public void Constructor() {
        mEntry = new Map<string, string>();
    }

    public void Constructor( Map<string, string> data ) {
        mEntry = data;
    }

    public int size() const {
        return mEntry.size();
    }

    public string operator[]( string column ) throws {
        return mEntry.get( column );
    }

    public string =operator( string ) const {
        string result;

        foreach ( Pair<string, string> column : mEntry ) {
            if ( result ) {
                result += " | ";
            }

            result += column.second;
        }

        return result;
    }

    private Map<string, string> mEntry;
}
