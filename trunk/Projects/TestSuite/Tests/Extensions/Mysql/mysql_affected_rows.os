#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int result;

		int handle = mysql_init();
		writeln("mysql_init() = " + handle);

		writeln("mysql_real_connect()");
		mysql_real_connect(handle, "192.168.0.22", 3306, "oscript", "oscript", "ts_parking");

		string query = "SELECT * FROM parking_tickets";

		result = mysql_query(handle, query);
		writeln("mysql_query(" + handle + ", \"" + query + "\") = " + result);

		if ( result != 0 ) {
			writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
			writeln("failed.");
			return;
		}

		result = mysql_affected_rows(handle);
		writeln("mysql_affected_rows(" + handle + ") = " + result);

		mysql_close(handle);
		writeln("mysql_close(" + handle + ")");

		writeln("done");
	}
}

