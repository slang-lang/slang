#!/usr/local/bin/oscript

public void Main(int argc, string argv) modify {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.bin", "wb");
		writeln("handle: " + file);

		result = fwritei(file, 17);
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

