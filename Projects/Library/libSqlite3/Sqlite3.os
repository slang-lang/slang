
import Connection;
import Exceptions;
import Result;


public namespace Sqlite3 { }

public object Sqlite3DB {
    public void Constructor( string filename ) {
        mConnection = new Sqlite3Connection( filename );
    }

    public void Destructor() {
        delete mConnection;
    }

    public int errCode() const {
        return sqlite3_errcode( mConnection.Handle );
    }

    public string errMsg() const {
        return sqlite3_errmsg( mConnection.Handle );
    }

    public Sqlite3Result exec( string query ) const throws {
        int handle = sqlite3_exec( mConnection.Handle, query );
        if ( !handle ) {
            throw new Sqlite3Exception( "invalid result set!" );
        }

        return new Sqlite3Result( handle );
    }

    private Sqlite3Connection mConnection;
}
