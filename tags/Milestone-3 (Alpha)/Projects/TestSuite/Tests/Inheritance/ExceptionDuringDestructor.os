#!/usr/local/bin/oscript

import System.Exception;

private object TestObject {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() throws {
		print("Destructor()");

		print("throw in destructor");
		//throw 42;
		throw new System.Exception(string 42);
	}
}

public void Main(int argc = 0, string argv = "") {
	try {
		TestObject obj = new TestObject();

		delete obj;
	}
	catch ( string e ) {
		print("caugth exception: " + e);
	}
}

