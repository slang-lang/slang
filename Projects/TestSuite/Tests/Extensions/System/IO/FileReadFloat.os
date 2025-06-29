#!/usr/bin/env slang

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.float", "r");
		writeln("handle: " + file);

		float result = freadf(file);
		writeln("freadf = " + result);

		assert( result == 173.139f );
	}
	catch {
		writeln("error during fread");
	}
	finally {
		result = fclose(file);
		writeln("fclose = " + result);
	}
}

