#!/usr/local/bin/oscript

public object TestObject {
	public void Constructor() {
	}
}

public int Main(int argc = 0, string args = "") {
	int lowerbound = 1;
	int upperbound = 100000;

	print("Starting performance test (by counting from " + lowerbound + " to " + upperbound + ")...");

	while ( lowerbound < upperbound ) {
		Object o = Object new TestObject();

		lowerbound++;
	}

	print("Finished performance test.");

	return 0;
}

