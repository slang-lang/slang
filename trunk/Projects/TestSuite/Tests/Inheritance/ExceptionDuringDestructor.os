#!/usr/local/bin/oscript

private object TestObject {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() throws {
		print("Destructor()");

		print("throw in destructor");
		throw 42;
	}
}

public void Main(int argc = 0, string argv = "") {
	try {
		TestObject obj = new TestObject();
	}
	catch ( int e ) {
		print("e.what() = " + e);
	}
}

