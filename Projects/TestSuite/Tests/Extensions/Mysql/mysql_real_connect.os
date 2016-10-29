#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int handle = mysql_init();

	writeln("mysql_real_connect()");

	mysql_real_connect(handle, "192.168.0.23", 3306, "oscript", "oscript", "ts_parking");

	writeln("done");
}

