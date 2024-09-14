
// library imports

// project imports
import Config;


public namespace DB {

    public int Handle;

    public void BeginTransaction() const {
        Execute( "BEGIN" );
    }

    public void CommitTransaction() const {
        Execute( "COMMIT" );
    }

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

    public string Error() const {
        return mysql_error(Handle);
    }

    public int Execute(string query) const throws {
        int error = mysql_query(DB.Handle, query);
        if ( error ) {
            throw mysql_error(Handle);
        }

        try { return mysql_store_result(Handle); }

        return 0;
    }

    public int getLastInsertId() const {
        int result = Query( "SELECT LAST_INSERT_ID() AS ID" );

        if ( mysql_fetch_row(result) ) {
                return cast<int>( mysql_get_field_value(result, "ID") );
        }

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

    public void RollbackTransaction() const {
        Execute( "ROLLBACK" );
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

