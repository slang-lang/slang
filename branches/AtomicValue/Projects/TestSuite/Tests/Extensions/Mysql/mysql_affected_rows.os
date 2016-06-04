#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int error = 0;
		int handle = 0;

		handle = mysql_init();
		writeln("mysql_init() = " + handle);

		mysql_real_connect(handle, "192.168.0.22", 3306, "oscript", "oscript", "ts_parking");
		writeln("mysql_real_connect()");

		string query = "SELECT * FROM parking_zones";

		error = mysql_query(handle, query);
		writeln("mysql_query(" + handle + ", \"" + query + "\") = " + error);

		if ( error != 0 ) {
			writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
			writeln("failed.");
			return;
		}

		int numAffectedRows = mysql_affected_rows(handle);
		writeln("mysql_affected_rows(" + handle + ") = " + numAffectedRows);

		mysql_close(handle);
		writeln("mysql_close(" + handle + ")");

		writeln("done");
	}
}

