#!/usr/local/bin/slang

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file  = fopen("file.bin", "wb");
		writeln("handle: " + file);

		assert( feof(file) );

		result = fclose(file);
		writeln("result = " + result);
	}
	catch ( string e ) {
		writeln("error during fopen: " + e);
	}
}

