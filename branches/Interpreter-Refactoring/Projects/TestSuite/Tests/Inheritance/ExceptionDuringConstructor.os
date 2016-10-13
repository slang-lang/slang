#!/usr/local/bin/oscript

import System.Exception;

private object TestObject {
	public void TestObject() throws {
		print("TestObject()");

		print("throw in constructor");
		//throw 42;
		throw new System.Exception("42");
	}

	public void ~TestObject() {
		print("~TestObject()");
	}
}

public void Main(int argc = 0, string argv = "") {
	try {
		TestObject obj = new TestObject();
	}
}

