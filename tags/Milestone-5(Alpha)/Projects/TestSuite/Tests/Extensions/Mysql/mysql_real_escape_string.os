#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int handle = mysql_init();
	writeln("mysql_init() = " + handle);

	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");
	writeln("mysql_real_connect()");

	string query = "SELECT * FROM parking_zones";
	writeln("mysql_real_escape_string(" + handle + ", \"" + query + "\") = " + mysql_real_escape_string(handle, query));

	mysql_close(handle);

	writeln("done.");
}

