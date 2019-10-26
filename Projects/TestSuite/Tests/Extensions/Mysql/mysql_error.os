#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	try {
		int handle = 0;

		handle = mysql_init();
		writeln("mysql_init() = " + handle);

		writeln("mysql_error(0) = " + mysql_error(/*dummy handle*/0));
		writeln("done.");
	}
	catch ( string e ) {
		print("Error: " + e);
	}
}

