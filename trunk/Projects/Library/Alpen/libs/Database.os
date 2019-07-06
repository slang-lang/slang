
// library imports

// project imports
import Config;


public namespace DB {

    public int Handle;

    public int Connect() modify throws {
        Handle = mysql_init();
        Handle = mysql_real_connect(Handle, Host, Port, User, Password, Database);

        if ( !Handle ) {
            throw "failed to connect to database " + Database;
        }

        return Handle;
    }

    public void Disconnect(int handle = 0) modify {
        mysql_close(handle ?: Handle);
    }

    public int Execute(string query) const throws {
        int error = mysql_query(DB.Handle, query);
        if ( error ) {
            throw mysql_error(Handle);
        }

        try { return mysql_store_result(Handle); }

        return 0;
    }

    public bool Insert(string query) const throws {
        int error = mysql_query(DB.Handle, query);
        if ( error ) {
            throw mysql_error(Handle);
        }

        try { return mysql_affected_rows(Handle) > 0; }

        return false;
    }

    public int Query(string query) const throws {
        int error = mysql_query(DB.Handle, query);
        if ( error ) {
            throw mysql_error(Handle);
        }

        try { return mysql_store_result(Handle); }

        return 0;
    }

    public bool Update(string query) const throws {
        int error = mysql_query(DB.Handle, query);
        if ( error ) {
            throw mysql_error(Handle);
        }

        try { return mysql_affected_rows(Handle) > 0; }

        return false;
    }

}
