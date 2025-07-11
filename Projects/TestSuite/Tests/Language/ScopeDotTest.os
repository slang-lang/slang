#!/usr/bin/env slang

public object TestObject {
	public int mValue;

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value) modify {
		mValue = value;
	}
}

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() {
	TestObject obj = new TestObject();

	obj.mValue = 1;
	print("obj.mValue = " + obj.mValue);

	obj.setValue(2);
	print("obj.getValue() = " + obj.getValue());

	return obj.mValue == 2;
}

