#!/usr/local/bin/oscript

import System.Exception;

public void Main(int argc, string args) throws {
	try {
		throw new OutOfBoundsException("out of bounds");
	}
	catch ( OutOfBoundsException e ) {
		assert(e);
		print("e.what() = " + e.what());
	}
}

