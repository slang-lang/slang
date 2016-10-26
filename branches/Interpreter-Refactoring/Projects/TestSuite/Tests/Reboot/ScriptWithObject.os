#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");
		mValue = value;
	}

	public void Destructor() {
		print("Destructor()");
	}

	public int getValue() const {
		return mValue;
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

	print("obj.getValue() = " + obj.getValue());

	TestObject obj2 = obj;

	assert( obj == obj2 );

	print("fine.");

	return 0;
}

