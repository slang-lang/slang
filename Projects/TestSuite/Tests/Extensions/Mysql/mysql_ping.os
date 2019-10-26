#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int error = 0;
	int handle = mysql_init();

	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");
	writeln("mysql_real_connect()");

	error = mysql_ping(handle);
	writeln("mysql_ping(" + handle + ") = " + error);

	mysql_close(handle);
	writeln("mysql_close(" + handle + ")");

	writeln("done");
}

