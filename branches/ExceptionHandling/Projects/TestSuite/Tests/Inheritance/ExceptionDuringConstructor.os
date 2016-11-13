#!/usr/local/bin/oscript

import System.Exception;

private object TestObject {
	public void Constructor() throws {
		print("Constructor()");

		print("throw in constructor");
		throw new Exception("42");
	}

	public void Destructor() {
		print("Destructor()");
	}
}

public void Main(int argc = 0, string argv = "") {
	try {
		TestObject obj = new TestObject();
	}
	catch ( Exception e ) {
		print("e.what() = " + e.what());
	}
}

