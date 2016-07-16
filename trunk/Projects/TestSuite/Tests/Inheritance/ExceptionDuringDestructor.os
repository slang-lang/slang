#!/usr/local/bin/oscript

import System.Exception;

private object TestObject {
	public void TestObject() {
		print("TestObject()");
	}

	public void ~TestObject() {
		print("~TestObject()");

		print("throw in destructor");
		//throw 42;
		throw new System.Exception(string 42);
	}
}

public object Main {
	public void Main(int argc = 0, string argv = "") {
		try {
			TestObject obj = new TestObject();
		}
	}
}

