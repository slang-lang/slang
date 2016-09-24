#!/usr/local/bin/oscript

public object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}

	public void ~TestObject() {
		print("~TestObject()");
	}
}

public object Main {
	public void Main(int argc, string args) {
		TestObject obj = new TestObject(173);

		print(obj.mValue);
		obj = null;

		assert(!obj);
	}
}

