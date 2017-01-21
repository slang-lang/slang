#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.bool", "rb");
		writeln("handle: " + file);

		bool result = freadb(file);
		writeln("freadb = " + result);

		assert( result == true );
	}
	catch {
		writeln("error during fread");
	}
	finally {
		result = fclose(file);
		writeln("fclose = " + result);
	}
}

