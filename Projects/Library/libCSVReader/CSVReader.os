
// library imports
import System.CharacterIterator;
import System.Collections.ICollection;
import System.Collections.IIterable;
import System.Collections.Vector;
import System.IO.File;

// project imports
import Row;
import HeaderEntry;


public object CSVReader implements ICollection, IIterable {
    public void Constructor( string filename = "", bool columnTitles = false ) {
        mColumnTitles = columnTitles;
        mData         = new Vector<Row>();
        mHeader       = new HeaderEntry();

        if ( filename ) {
            open( filename, columnTitles );
        }
    }

    // ICollection interface implementation
    // {
    public Row operator[]( int index ) const {
        return mData.at( index );
    }

    public Row at( int index ) const {
        return mData.at( index );
    }

    public int size() const {
        return mData.size();
    }
    // }

    // IIterable interface implementation
    // {
    public Iterator<Row> getIterator() const {
        return mData.getIterator();
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

    public string =operator( string ) const {
        return "CSVReader{" + mData.size() + " rows}";
    }

    private bool parseFile( string filename ) modify throws {
        var file = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );
        if ( !file.isOpen() ) {
            throw "Failed to open file \"" + filename + "\"";
        }

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

    private bool parseString( string content ) modify {
        var charIt = new CharacterIterator( content );
        bool isFirstLine = true;

        string char;
        string line;
        while ( charIt.hasNext() ) {
            if ( ( char = charIt.next() ) == LINEBREAK ) {
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
    private Vector<Row> mData;
    private HeaderEntry mHeader;
    private string mFilename;
}
