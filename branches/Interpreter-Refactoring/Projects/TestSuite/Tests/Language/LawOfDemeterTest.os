#!/usr/local/bin/oscript

public object TestObject {
	public int mPublicMember;
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject();
	obj.mPublicMember = 0;
}

