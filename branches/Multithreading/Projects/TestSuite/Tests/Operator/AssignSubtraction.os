#!/usr/local/bin/oscript

public object TestObject {
	public int mValue;

	public TestObject operator-(int other) modify {
		print("operator-");

		mValue -= other;

		return this;
	}
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject();

	obj -= 1;
}

