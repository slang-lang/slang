#!/usr/local/bin/slang

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.double", "r");
		writeln("handle: " + file);

		double result = freadd(file);
		writeln("freadd = " + result);

		assert( result == 173.139d );
	}
	catch {
		writeln("error during fread");
	}
	finally {
		result = fclose(file);
		writeln("fclose = " + result);
	}
}

