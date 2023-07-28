
// Library imports
import System.Collections.Iterator;
import System.Collections.Vector;

// Project imports
import Connection;
import Exceptions;


public namespace Sqlite3 { }

public object Sqlite3Entry const {
    public string Name const;
    public string Value const;

    public void Constructor( string name, string value ) {
        Name = name;
        Value = value;
    }

    public string =operator( string ) const {
        return "{ \"" + Name + "\": \"" + Value + "\" }";
    }
}

public object Sqlite3Row implements IIterable {
    public Vector<Sqlite3Entry> Entries const;

	public void Constructor( int result ) {
		Entries = new Vector<Sqlite3Entry>();

        while ( sqlite3_next_field( result ) ) {
            Entries.push_back( new Sqlite3Entry( sqlite3_get_field_name( result ), sqlite3_get_field_value( result ) ) );
        }
	}

    public Iterator<Sqlite3Entry> getIterator() const {
        return Entries.getIterator();
    }

    public Sqlite3Entry operator[]( int index ) const {
        return Entries[index];
    }

    public string =operator( string ) const {
        string result;

        foreach ( Sqlite3Entry entry : Entries ) {
            if ( result ) {
                result += ",";
            }

            result += cast<string>( entry );
        }

        return result;
    }
}

public object Sqlite3Result implements IIterable {
    public Vector<Sqlite3Row> Rows const;

    public void Constructor( int result ) {
        Rows = new Vector<Sqlite3Row>();

        while ( sqlite3_next_row( result ) ) {
            Rows.push_back( new Sqlite3Row( result ) );
        }

        sqlite3_free_result( result );
    }

    public Iterator<Sqlite3Row> getIterator() const {
        return Rows.getIterator();
    }

    public Sqlite3Row operator[]( int index ) const {
        return Rows[index];
    }

    public string =operator( string ) const {
        string result;

        foreach ( Sqlite3Row row : Rows ) {
            if ( result ) {
                result += ",";
            }

            result += "[" + cast<string>( row ) + "]";
        }

        return result;
    }
}

