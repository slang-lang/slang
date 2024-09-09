#!/usr/local/bin/slang

private object TestObject {
	public int mValue;

	public void setValue(int value) const {
		mValue = value;
	}
}

public void Main(int argci = 0, string args = "") {
	TestObject obj = new TestObject();

	obj.setValue(173);
}

