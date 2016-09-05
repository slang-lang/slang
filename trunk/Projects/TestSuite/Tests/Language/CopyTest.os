#!/usr/local/bin/oscript

public object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}
}

public object Main {
	public void Main(int argc, string args) {
		TestObject obj1 = new TestObject(173);
		TestObject obj2;

		obj2 = copy obj1;

		assert(obj2);
	}
}

