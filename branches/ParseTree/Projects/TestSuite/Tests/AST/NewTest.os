#!/usr/local/bin/oscript

public object TestObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public int getValue() const {
		return mValue;
	}
}

public void Main(int argc, string args) {
	TestObject obj = new TestObject(173);

	{
		TestObject obj = new TestObject(1389);

		//print("obj.getValue() = " + obj.getValue());
	}
}

