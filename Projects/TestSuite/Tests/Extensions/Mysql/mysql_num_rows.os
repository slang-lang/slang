#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		writeln("mysql_real_connect()");
		mysql_real_connect("192.168.0.22", 3306, "oscript", "oscript", "ts_parking");

		string query = "SHOW TABLES";

		writeln("mysql_query(\"" + query + "\")");
		int result = mysql_query(query);

		if ( result != 0 ) {
			writeln("mysql_error() = " + mysql_error());
			writeln("failed.");
			return;
		}

		result = mysql_num_rows(/*dummy handle*/ 0);
		writeln("mysql_num_rows(0) = " + result);

		writeln("done");
	}
}

