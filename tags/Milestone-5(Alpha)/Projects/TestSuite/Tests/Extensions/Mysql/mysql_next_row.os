#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int result;
	int result_handle;

	int handle = mysql_init();
	writeln("mysq_init() = " + handle);

	writeln("mysql_real_connect()");
	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");

	string query = "SELECT * FROM parking_zones";

	result = mysql_query(handle, query);
	writeln("mysql_query(" + handle + ", \"" + query + "\") = " + result);

	if ( result != 0 ) {
		writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
		writeln("failed.");
		return;
	}

	result_handle = mysql_store_result(handle);
	writeln("mysql_store_result(" + handle + ") = " + result_handle);

	result = mysql_num_rows(result_handle);
	writeln("mysql_num_rows(" + result_handle + ") = " + result);

	mysql_close(handle);
	writeln("mysql_close(" + handle + ")");

	writeln("done");
}

