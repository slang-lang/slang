#!/usr/local/bin/oscript

import System.IO.File;

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	try {
		System.IO.File file = new System.IO.File("file", "wb");
		assert( file.isOpen() );

		file.write(1731389);
		file.rewind();

		file.close();
	}
	catch {
		writeln("error during fwrite");

		return false;
	}

	try {
		System.IO.File file = new System.IO.File("file", "r");
		//file.open("file", "r");	// this throws an exception as long as the file is still open
		assert( file.isOpen() );

		int value = file.readInt();
		writeln("value = " + value);

		file.rewind();

		value = file.readInt();
		writeln("value = " + value);

		file.close();
	}
	catch {
		writeln("error during fread");

		return false;
	}

	return true;
}

