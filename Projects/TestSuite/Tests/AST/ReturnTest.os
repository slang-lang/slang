#!/usr/local/bin/oscript

public int Main(int argc = 1, string args = "") {
	print("Main(" + argc + ", \"" + args + "\")");

	return (10 - 2 * 4 - 1);

	//return ReturnOne();
}

private int ReturnOne() const {
	print("ReturnOne()");

	return (10 - 2 * 4 - 1);
}

