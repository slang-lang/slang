#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int handle = mysql_init();
		writeln("mysql_init() = " + handle);

		string query = "SELECT * FROM parking_zones";
		writeln("mysql_real_escape_string(\"" + handle + ", " + query + "\") = " + mysql_real_escape_string(handle, query));

		writeln("done.");
	}
}

