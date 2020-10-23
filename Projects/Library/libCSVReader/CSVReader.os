
// library imports
import System.Collections.ICollection;
import System.Collections.IIterable;
import System.Collections.Vector;
import System.IO.File;

// project imports
import DataEntry;
import HeaderEntry;


public object CSVReader implements ICollection, IIterable {
    public void Constructor( string filename = "", bool columnTitles = true ) {
        mColumnTitles = columnTitles;
        mData = new Vector<DataEntry>();
        mHeader = new HeaderEntry();

        if ( filename ) {
            open( filename, columnTitles );
        }
    }

    // ICollection interface implementation
    // {

    public DataEntry operator[]( int index ) const {
        return mData.at( index );
    }

    public DataEntry at( int index ) const {
        return mData.at( index );
    }

    public int size() const {
        return mData.size();
    }

    // }

    // IIterable interface implementation
    // {

    public Iterator<DataEntry> getIterator() const {
        return new Iterator<DataEntry>( ICollection this );
    }

    // }

    public HeaderEntry const header() const {
        return mHeader;
    }

    public bool open( string filename = "", bool columnTitles = true ) modify {
        if ( columnTitles ) {
            mColumnTitles = columnTitles;
        }
        if ( filename ) {
            mFilename = filename;
        }

        return parseFile( filename );
    }

    private bool parseFile( string filename ) modify throws {
        var file = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );

        bool isFirstLine = true;

	string char;
        string line;
        while ( !file.isEOF() ) {
            if ( ( char = file.readChar() ) == LINEBREAK ) {
                if ( isFirstLine ) {
                    isFirstLine = false;

                    mHeader.parse( line );

                    if ( !mColumnTitles ) {
                        mData.push_back( mHeader.produceEntry( line ) );
                    }
                }
		else {
                    mData.push_back( mHeader.produceEntry( line ) );
                }

                line = "";

                continue;
            }

            line += char;
        }

        return true;
    }

    private bool mColumnTitles;
    private Vector<DataEntry> mData;
    private HeaderEntry mHeader;
    private string mFilename;
}

