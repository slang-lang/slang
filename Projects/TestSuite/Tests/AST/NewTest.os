#!/usr/local/bin/slang

public object TestObject {
	public int mValue;

	public void Constructor(int value = 173) {
		print("Constructor(" + value + ")");

		mValue = value;
	}

	public int getValue() const {
		return mValue;
	}
}

public void Main(int argc = 1, string args = "") modify {
	TestObject obj = new TestObject(173);

	{
		TestObject obj = new TestObject(1389);

		//print("obj.getValue() = " + obj.getValue());
	}
}

