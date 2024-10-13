
// library imports
import System.Collections.Vector;
import System.StringIterator;

// project imports
import Settings;


public object HeaderEntry implements Row {
    public void Constructor() {
        mColumns = new Vector<string>();
    }

    // TODO: move parsing to CSVReader and re-use StringIterator for every line instead of creating a new instance per line
    public void parse( string line ) modify {
        mColumns.clear();

        var columnIt = new StringIterator( line, Settings.SEPARATOR );
        while ( columnIt.hasNext() ) {
            mColumns.push_back( columnIt.next() );
        }
    }

    public Row produceEntry() const {
        var entry = new Vector<string>();

        foreach ( string column : mColumns ) {
            entry.push_back( column );
        }

        return new Row( entry );
    }

    public Row produceEntry( string line ) const {
        var entry = new Vector<string>();

        int columnIdx;
        var columnIt = new StringIterator( line, Settings.SEPARATOR );

        while ( columnIt.hasNext() ) {
            var column = mColumns.at( columnIdx );      // TODO: replace this with a simple index

            entry.push_back( columnIt.next() );

            columnIdx++;
        }

        return new Row( entry );
    }

    public override int size() const {
        return mColumns.size();
    }

    public override string operator[]( int index ) throws {
        return mColumns[ index ];
    }

    public override string =operator( string ) const {
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
