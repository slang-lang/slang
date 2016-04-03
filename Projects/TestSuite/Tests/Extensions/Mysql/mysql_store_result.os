#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int handle = mysql_init();

		int result;
		int result_handle;

		writeln("mysql_real_connect()");
		mysql_real_connect(handle, "192.168.0.22", 3306, "oscript", "oscript", "ts_parking");

		string query = "SELECT * FROM parking_zones";

		result = mysql_query(handle, query);
		writeln("mysql_query(" + handle + ", \"" + query + "\") = " + result);

		if ( result != 0 ) {
			writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
			writeln("failed.");
			return;
		}

		result_handle = mysql_store_result(handle);
		writeln("mysql_store_result(0) = " + result_handle);

		writeln("mysql_close(" + handle + ") = " + mysql_close(handle));

		writeln("done");
	}
}

