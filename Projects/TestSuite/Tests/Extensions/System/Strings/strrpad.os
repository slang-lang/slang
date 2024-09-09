#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: strrpad()");

	string value = "pad right";
	int length = 10;
	string pattern = ".";

	print("strrpad(" + value + ", " + length + ", \"" + pattern + "\") = " + strrpad(value, length, pattern));

	return strrpad(value, length, pattern) == "pad right..........";
}

private bool TestCase2() const {
	print("TestCase 2: strrpad() throw");

	try {
		print(strrpad("bla", -2, "."));

		assert(!"we should never get here!");
	}
	catch ( string e ) {
		print("caught exception: " + e);

		return true;
	}

	return false;
}

