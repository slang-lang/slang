
// load extension
import extension libSlangSQLite3;


public namespace Sqlite3 { }

public object Sqlite3Connection {
    public string Filename const;
    public int Handle const;

    public void Constructor( string filename ) {
        Filename = filename;

        Handle = sqlite3_open( Filename );
    }

    public void Destructor() {
        sqlite3_close( Handle );

        Handle = 0;
    }

    public bool isOpen() const {
        return Handle != 0;
    }
}

