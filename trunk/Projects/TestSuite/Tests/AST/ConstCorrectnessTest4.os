#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public int getValue() const {
		return this.mValue;
	}
	public void setValue(int value) modify {
		this.mValue = value;
	}
}

private object OtherObject {
	public TestObject createTestObject(int value) const static {
		TestObject obj = new TestObject(666);
		obj.setValue(value);

		return obj;
	}
}

public void Main(int argc = 0, string args = "") modify {
	TestObject obj = OtherObject.createTestObject(111);

	print("obj.getValue() = " + obj.getValue());

	obj.setValue(1389);
}

