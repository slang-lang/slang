#!/usr/local/bin/oscript

private void BreakOnException() const throws {
	print("Break on exception...");

	try {
		throw new string("this is an exception");
	}
	catch ( string e ) {
		print("catch: " + e);
	}
	finally {
		print("finally");
	}
}

public int Main(int argc, string args) {
	BreakOnException();

	return 0;
}

