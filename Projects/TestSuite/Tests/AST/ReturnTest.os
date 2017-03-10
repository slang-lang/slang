#!/usr/local/bin/oscript

public int Main(int argc = 1, string args = "") {
	print("Main(" + argc + ", \"" + args + "\")");

	int value = ReturnOne();
	print("value = " + value);

	return value;
}

private int ReturnOne() const {
	print("ReturnOne()");

	return 10 - 2 * 4 - 1;
}

/* // this has to fail
private void VoidMethod() {
	return 1;
}
*/

/* // this has to fail
private int IntMethod() {
	// missing return statement
}
*/

