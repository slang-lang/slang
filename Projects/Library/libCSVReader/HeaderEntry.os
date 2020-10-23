
// library imports
import System.Collections.Vector;
import System.StringIterator;

// project imports
import Settings;


public object HeaderEntry {
    public void Constructor() {
        mColumns = new Vector<string>();
    }

    public void parse( string line ) modify {
        mColumns.clear();

        var columnIt = new StringIterator( line, Settings.SEPARATOR );
        while ( columnIt.hasNext() ) {
            mColumns.push_back( columnIt.next() );
        }
    }

    public DataEntry produceEntry() const {
        var entry = new Map<string, string>();

        foreach ( string column : mColumns ) {
            entry.insert( column, "" );
        }

        return new DataEntry( entry );
    }

    public DataEntry produceEntry( string line ) const {
        var entry = new Map<string, string>();

        int columnIdx;
        var columnIt = new StringIterator( line, Settings.SEPARATOR );

        while ( columnIt.hasNext() ) {
            var column = mColumns.at( columnIdx );

            entry.insert( column, columnIt.next() );

            columnIdx++;
        }

        return new DataEntry( entry );
    }

    public string =operator( string ) const {
        string result;

        foreach ( string column : mColumns ) {
            if ( result ) {
                result += " | ";
            }

            result += column;
        }

        return result;
    }

    private Vector<string> mColumns;
}

