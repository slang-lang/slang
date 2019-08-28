#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int result;

	int handle = mysql_init();

	writeln("mysql_real_connect()");
	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");

	mysql_close(handle);
	writeln("mysql_close()");

	writeln("done");
}

