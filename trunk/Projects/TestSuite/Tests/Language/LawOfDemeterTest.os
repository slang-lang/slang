#!/usr/local/bin/oscript

// THIS WILL FAIL

public object TestObject {
	public int mPublicMember;
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject();
	obj.mPublicMember = 0;

	assert(0);
}

