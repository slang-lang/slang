
private namespace DB {

	public string Database const = "repository";
	public string Host const = "127.0.0.1";
	public string Password const = "admin*";
	public int Port const = 3306;
	public string User const = "root";

	public int Error = 0;
	public int Handle = 0;

	public bool connect() {
		Handle = mysql_init();
		Handle = mysql_real_connect( Handle, Host, Port, User, Password, Database );

		if ( !Handle ) {
			print( "failed to initialize MySQL connection!" );
			return false;
		}

		return true;
	}

	public bool disconnect() {
		mysql_close( Handle );

		return true;
	}

}

