#!/usr/local/bin/slang

import System.String;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: strpos(\"This is a string\", 3)");

	string str = "This is a string";
	string ch = strpos(str, 3);
	print("strpos = \"" + ch + "\"");

	return ch == "s";
}

private bool TestCase2() const {
	print("TestCase 2: strpos with SizeException");

	try {
		string str = "bla";
		string ch = strpos(str, 10);

		assert(!"we should not get here");
		return false;
	}
	catch (string e ) {
		print(e);

		return true;
	}

	return false;
}

