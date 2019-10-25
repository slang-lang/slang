#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int error = 0;
	int handle = 0;
	int result_handle = 0;

	handle = mysql_init();
	writeln("mysql_init() = " + handle);

	handle = mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");
	writeln("mysql_real_connect() = " + handle);

	string query = "SELECT * FROM parking_zones";

	error = mysql_query(handle, query);
	writeln("mysql_query(" + handle + ", \"" + query + "\") = " + error);

	if ( error != 0 ) {
		writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
		writeln("failed.");
		return;
	}

	result_handle = mysql_store_result(handle);
	writeln("mysql_store_result(" + handle + ") = " + result_handle);

	int numFields = mysql_field_count(handle);
	writeln("mysql_field_count(" + handle + ") = " + numFields);

	mysql_free_result(result_handle);
	writeln("mysql_free_result(" + result_handle + ")");

	mysql_close(handle);
	writeln("mysql_close(" + handle + ")");

	writeln("done");
}

