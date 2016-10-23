#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.int", "r");
		writeln("handle: " + file);

		int result = freadi(file);
		writeln("freadi = " + result);
	}
	catch {
		writeln("error during fread");
	}
	finally {
		result = fclose(file);
		writeln("fclose = " + result);
	}
}

