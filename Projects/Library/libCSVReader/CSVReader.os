
// library imports
import System.CharacterIterator;
import System.Collections.ICollection;
import System.Collections.IIterable;
import System.Collections.Vector;
import System.IO.File;

// project imports
import Row;
import Settings;


public object CSVReader implements ICollection, IIterable {
    public void Constructor( string filename = "", bool columnTitles = false ) {
        mColumnTitles = columnTitles;
        mData         = new Vector<Row>();

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

    public Row const header() const {
        return mData[ 0 ];
    }

    public bool open( string filename = "", bool headerOnly = false ) modify throws {
        if ( filename ) {
            mFilename = filename;
        }

        var file = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );
        if ( !file.isOpen() ) {
            throw "Failed to open file \"" + filename + "\"";
        }

        return parseString( file.readString( file.getSize() ), headerOnly );
    }

    public string =operator( string ) const {
        return "CSVReader{" + mData.size() + " rows}";
    }

    private bool parseString( string content, bool headerOnly = false ) modify {
        var charIt = new CharacterIterator( content );


        string char;
        string line;
        while ( charIt.hasNext() ) {
            if ( ( char = charIt.next() ) == LINEBREAK ) {
                {   // parse row
                    var row = new Row();

                    var columnIt = new StringIterator( line, Settings.SEPARATOR );
                    while ( columnIt.hasNext() ) {
                        row.push_back( columnIt.next() );
                    }
                    line = "";

                    mData.push_back( row );
                }

                if ( headerOnly ) {
                    break;
                }

                continue;
            }

            line += char;
        }

        return true;
    }

    private bool mColumnTitles;
    private Vector<Row> mData;
    private string mFilename;
}
