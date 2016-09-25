#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string argv) {
		int error = 0;
		int handle = mysql_init();

		mysql_real_connect(handle, "192.168.0.23", 3306, "oscript", "oscript", "ts_parking");
		writeln("mysql_real_connect()");

		error = mysql_ping(handle);
		writeln("mysql_ping(" + handle + ") = " + error);

		mysql_close(handle);
		writeln("mysql_close(" + handle + ")");

		writeln("done");
	}
}

