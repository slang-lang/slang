#!/usr/local/bin/oscript

import System.Exception;
import System.String;

private object TestObject {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() throws {
		print("Destructor()");

		print("throw in destructor");
		throw new Exception("42");
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

