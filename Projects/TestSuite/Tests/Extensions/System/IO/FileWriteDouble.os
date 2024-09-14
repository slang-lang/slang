#!/usr/local/bin/slang

public void Main(int argc, string argv) modify {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.double", "wb");
		writeln("handle: " + file);

		result = fwrited(file, 173.139d);
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

