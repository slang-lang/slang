#!/usr/local/bin/oscript

private int Function1() {
	print("Function1()");

	return 1;
}

public int Main(int argc, string args) {
	print("SimpleScript: Main(" + argc + ", " + args + ")");

	int result = Function1();
	print("Function1() returned " + result);

	return 0;
}

