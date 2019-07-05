
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

}
