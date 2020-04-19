#!/usr/local/bin/slang

public void Main(int argc, string argv) {
	int handle = mysql_init();
	writeln("mysql_init() = " + handle);

	writeln("done.");
}

