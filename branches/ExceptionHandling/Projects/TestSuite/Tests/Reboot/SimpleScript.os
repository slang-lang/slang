#!/usr/local/bin/oscript

private int Function1(int value) {
	print("Function1(" + value + ")");

	return value;
}

public int Main(int argc, string args) {
	print("SimpleScript: Main(" + argc + ", " + args + ")");

	int result = Function1(173);
	print("Function1() returned " + result);

	return 0;
}

