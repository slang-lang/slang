#!/usr/local/bin/slang

import System.IO.File;

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: using string as access modifier");

	try {
		System.IO.File file = new System.IO.File("file", "w");
		assert( file.isOpen() );

		file.write(1731389);
		file.rewind();

		file.close();
	}
	catch {
		print("error during fwrite");

		return false;
	}

	try {
		System.IO.File file = new System.IO.File("file", "r");
		//file.open("file", "r");	// this throws an exception as long as the file is still open
		assert( file.isOpen() );

		int value = file.readInt();
		print("value = " + value);

		file.rewind();

		value = file.readInt();
		print("value = " + value);

		file.close();
	}
	catch {
		print("error during fread");

		return false;
	}

	return true;
}

private bool TestCase2() const {
	print("TestCase 2: using System.IO.File.AccessMode");

	try {
		System.IO.File file = new System.IO.File("file", System.IO.File.AccessMode.ReadOnly);
		assert( file.isOpen() );

		file.write(1731389);
		file.rewind();

		file.close();
	}
	catch {
		print("error during fwrite");

		return false;
	}

	try {
		System.IO.File file = new System.IO.File("file", System.IO.File.AccessMode.ReadOnly);
		//file.open("file", "r");	// this throws an exception as long as the file is still open
		assert( file.isOpen() );

		int value = file.readInt();
		print("value = " + value);

		file.rewind();

		value = file.readInt();
		print("value = " + value);

		file.close();
	}
	catch {
		print("error during fread");

		return false;
	}

	return true;
}

