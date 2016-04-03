#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int result;

		int handle = mysql_init();

		writeln("mysql_real_connect()");
		mysql_real_connect(handle, "192.168.0.22", 3306, "oscript", "oscript", "ts_parking");

		result = mysql_close(handle);
		writeln("mysql_close() = " + result);

		writeln("done");
	}
}

