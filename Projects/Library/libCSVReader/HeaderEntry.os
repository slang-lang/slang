
// library imports
import System.Collections.Vector;
import System.StringIterator;

// project imports
import Settings;


public object HeaderEntry implements Row {
    public void Constructor() {
        mColumns = new Row();
    }

    public int getIdx( string column ) const {
        for ( var idx = 0; idx < mColumns.size(); idx++ ) {
            if ( mColumns[ idx ] == column ) {
                return idx;
            }
        }

        return -1;
    }

    public void parse( string line ) modify {
        mColumns.clear();

        var columnIt = new StringIterator( line, Settings.SEPARATOR );
        while ( columnIt.hasNext() ) {
            mColumns.push_back( columnIt.next() );
        }
    }

    public Row produceEntry() const {
        var row = new Row();

        foreach ( string column : mColumns.getIterator() ) {
            row.push_back( column );
        }

        return row;
    }

    public Row produceEntry( string line ) const {
        var row = new Row();

        int columnIdx;
        var columnIt = new StringIterator( line, Settings.SEPARATOR );

        while ( columnIt.hasNext() ) {
            var column = mColumns.at( columnIdx );      // TODO: replace this with a simple index

            row.push_back( columnIt.next() );

            columnIdx++;
        }

        return row;
    }

    public override int size() const {
        return mColumns.size();
    }

    public override string operator[]( int index ) throws {
        return mColumns[ index ];
    }

    public override string =operator( string ) const {
        string result;

        foreach ( string column : mColumns.getIterator() ) {
            if ( result ) {
                result += " | ";
            }

            result += column;
        }

        return result;
    }

    private Row mColumns;
}
