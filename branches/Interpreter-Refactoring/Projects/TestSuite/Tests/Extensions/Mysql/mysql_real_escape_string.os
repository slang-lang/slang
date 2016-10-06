#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int handle = mysql_init();
		writeln("mysql_init() = " + handle);

		mysql_real_connect(handle, "192.168.0.23", 3306, "oscript", "oscript", "ts_parking");
		writeln("mysql_real_connect()");

		string query = "SELECT * FROM parking_zones";
		writeln("mysql_real_escape_string(" + handle + ", \"" + query + "\") = " + mysql_real_escape_string(handle, query));

		mysql_close(handle);

		writeln("done.");
	}
}

