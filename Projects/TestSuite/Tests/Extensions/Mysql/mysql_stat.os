#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int handle = mysql_init();

	handle = mysql_real_connect(handle, "192.168.0.23", 0, "oscript", "oscript", "");
	if ( !handle ) {
		writeln("error while connecting to database!");
		return;
	}

	string stat = mysql_stat(handle);
	writeln("mysql_stat(" + handle + ") = " + stat);

	mysql_close(handle);
}

