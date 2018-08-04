#!/usr/local/bin/oscript

public void Main(int argc, string argv) modify {
	int handle = 0;

	handle = mysql_init();
	writeln("mysql_init() = " + handle);

	writeln("mysql_info(" + handle + ") = " + mysql_info(handle));

	mysql_close(handle);
	writeln("mysql_close(" + handle + ")");

	writeln("done.");
}

