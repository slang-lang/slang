#!/usr/local/bin/oscript

import System.Exception;

private object TestObject {
	public void Constructor() throws {
		print("Constructor()");

		print("throw in constructor");
		//throw 42;
		throw new System.Exception("42");
	}

	public void Destructor() {
		print("Destructor()");
	}
}

public void Main(int argc = 0, string argv = "") {
	try {
		TestObject obj = new TestObject();
	}
}

