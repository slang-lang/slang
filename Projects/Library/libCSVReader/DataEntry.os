
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

    public string operator[]( string column ) throws {
        return mEntry.get( column );
    }

    public string =operator( string ) const {
        string result;

        foreach ( Object column : mEntry ) {
            if ( result ) {
                result += " | ";
            }

            result += ( Pair<string, string> column ).second;
        }

        return result;
    }

    private Map<string, string> mEntry;
}
