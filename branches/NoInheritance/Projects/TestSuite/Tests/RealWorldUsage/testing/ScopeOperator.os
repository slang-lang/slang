#!/usr/local/bin/oscript

public object TestObject {
	public int mValue;
}

public void Main(int argc, string args) {
	Object obj = new TestObject();

	(TestObject obj).mValue = 173;

	assert(obj.mValue == 173);
}

