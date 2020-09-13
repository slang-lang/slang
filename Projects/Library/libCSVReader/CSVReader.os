
// library imports
import System.Collections.Map;
import System.Collections.Vector;
import System.IO.File;
import System.StringIterator;

// project imports


public object CSVReader {
    public void Constructor( string filename = "" ) {
        mData = new Vector<DataEntry>();
        mHeader = new HeaderEntry();

        if ( filename ) {
            open( filename );
        }
    }

    public DataEntry operator[]( int index ) const {
        return mData.at( index );
    }

    public HeaderEntry const header() const {
        return mHeader;
    }

    public bool open( string filename = "" ) modify {
        if ( filename ) {
            mFilename = filename;
        }

        return parseFile( filename );
    }

    private bool parseFile( string filename ) modify throws {
        var file = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );

        bool isFirstLine = true;

        string line;
        while ( !file.isEOF() ) {
            string c = file.readChar();
            if ( c == LINEBREAK ) {
                if ( !isFirstLine ) {
                    mData.push_back( mHeader.produceEntry( line ) );
                }
                else {
                    mHeader.parse( line );
                }

                line = "";
                isFirstLine = false;

                continue;
            }

            line += c;
        }

        return true;
    }

    private Vector<DataEntry> mData;
    private HeaderEntry mHeader;
    private string mFilename;
}


public object HeaderEntry {
    public void Constructor() {
        mColumns = new Vector<string>();
    }

    public void parse( string line ) modify {
        mColumns.clear();

        var columnIt = new StringIterator( line, "," );
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
        var columnIt = new StringIterator( line, "," );

        while ( columnIt.hasNext() ) {
            var column = mColumns.at(columnIdx);

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

public object DataEntry {
    public void Constructor() {
        mEntry = new Map<string, string>();
    }

    public void Constructor( Map<string, string> data ) {
        mEntry = data;
    }

    public string operator[]( string column ) throws {
        return mEntry[column];
    }

    public string =operator( string ) const {
        string result;

        foreach ( Object column : mEntry ) {
            if ( result ) {
                result += " | ";
            }

            result += (Pair<string, string> column).second;
        }

        return result;
    }

    private Map<string, string> mEntry;
}
