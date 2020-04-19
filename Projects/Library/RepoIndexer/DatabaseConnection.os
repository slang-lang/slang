
private namespace DB {
	public int mError = 0;
	public int mHandle = 0;

	public string Database const = "repository";
	public string Host const = "127.0.0.1";
	public string Password const = "admin*";
	public int Port const = 3306;
	public string User const = "root";

	public bool connect(bool debugprint = false) {
		mHandle = mysql_init();

		if ( debugprint ) {
			printSettings();
		}

		mHandle = mysql_real_connect(mHandle, Host, Port, User, Password, Database);

		if ( !mHandle ) {
			print("failed to initialize MySQL connection!");
			return false;
		}

		return true;
	}

	public bool disconnect() {
		mysql_close(mHandle);

		return true;
	}

	public void printSettings() const {
		print("Connection settings:");
		print("Host = " + Host);
		print("Port = " + Port);
		print("User = " + User);
		print("Database = " + Database);
	}

}

