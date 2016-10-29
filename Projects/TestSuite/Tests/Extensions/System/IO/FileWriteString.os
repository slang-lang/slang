#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.string", "ctw");
		writeln("handle: " + file);

		result = fwrites(file, "foo bar");
		writeln("result = " + result);
	}
	catch {
		writeln("error during fwrite");
	}
	finally {
		result = fclose(file);
		writeln("result = " + result);
	}
}

