#!/usr/local/bin/oscript

import System.Integer;


public object TestObject {
	public int mValue;

	public string toString() const {
		return string mValue;
	}
}

public void Main(int argc, string args) {
	TestObject testObj = new TestObject();
	testObj.mValue = 173;

	Object obj = Object testObj;

	assert((TestObject obj).mValue == 173);

	print("" + (TestObject obj).mValue);
	print((TestObject obj).mValue + 1);
	print((TestObject testObj).toString());

	var i = new Integer(1389);
	print((i + 2).toString());
	print((new Integer(0664)).toString());
}

