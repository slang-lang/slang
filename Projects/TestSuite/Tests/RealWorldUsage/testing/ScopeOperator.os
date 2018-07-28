#!/usr/local/bin/oscript

public object TestObject {
	public int mValue;
}

public void Main(int argc, string args) {
	TestObject testObj = new TestObject();
	testObj.mValue = 173;

	Object obj = Object testObj;

	assert((TestObject obj).mValue == 173);

	print("" + (TestObject obj).mValue);
}

