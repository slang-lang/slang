#!/usr/local/bin/oscript

public object TestObject {
	public void Constructor() {
	}
}

public object AnotherObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}
}

public int Main(int argc = 0, string args = "") {
	int lowerbound = 1;
	int upperbound = 100000;

	print("Starting performance test (by counting from " + lowerbound + " to " + upperbound + ")...");

	while ( lowerbound < upperbound ) {
		TestObject t = new TestObject();
		//AnotherObject a = new AnotherObject(1);

		lowerbound++;
	}

	print("Finished performance test.");

	return 0;
}

