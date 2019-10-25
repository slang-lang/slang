#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int handle = mysql_init();

	handle = mysql_real_connect(handle, "127.0.0.1", 3306, "root", "", "test_objectivescript");
	if ( !handle ) {
		writeln("error while connecting to database!");
		return;
	}

	string stat = mysql_stat(handle);
	writeln("mysql_stat(" + handle + ") = " + stat);

	mysql_close(handle);
}

