#!/usr/bin/env slang

public void Main(int argc, string argv) {
	int error = 0;
	int handle = mysql_init();
	int result_handle = 0;

	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");
	writeln("mysql_real_connect()");

	string query = "SELECT * FROM parking_zones";

	error = mysql_query(handle, query);
	writeln("mysql_query(" + handle + ", \"" + query + "\") = " + error);

	if ( error != 0 ) {
		writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
		writeln("failed.");
		return;
	}

	result_handle = mysql_use_result(handle);
	writeln("mysql_use_result(" + handle + ") = " + result_handle);

	mysql_close(handle);
	writeln("mysql_close(" + handle + ")");

	writeln("done");
}

