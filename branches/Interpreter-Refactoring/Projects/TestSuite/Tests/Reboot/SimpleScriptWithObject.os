#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public void TestObject(int value) {
		print("TestObject(" + value + ")");
		mValue = value;
	}
}

private int Function1(int value) {
	print("Function1(" + value + ")");

	return value;
}

public int Main(int argc, string args) {
	print("SimpleScript: Main(" + argc + ", " + args + ")");

	int result = Function1(173);

	TestObject obj = new TestObject(result * 10000 + 1389);

	print("obj.mValue = " + obj.mValue);

	return 0;
}

