#!/usr/local/bin/oscript

private namespace NS {
private object TestObject {
	public int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");
		mValue = value;
	}

	public void Destructor() {
		print("Destructor()");
	}
}
}

private int Function1(int value) {
	print("Function1(" + value + ")");

	return value;
}

public int Main(int argc, string args) {
	print("SimpleScript: Main(" + argc + ", " + args + ")");

	int result = Function1(173);

	NS.TestObject obj = new NS.TestObject(result * 10000 + 1389);

	print("obj.mValue = " + obj.mValue);

	delete obj;
	assert(!obj);

	print("fine.");

	return 0;
}

