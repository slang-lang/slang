#!/usr/local/bin/slang

public void Main(int argc = 1, string args = "") {
	print("Main(" + argc + ", \"" + args + "\")");

	exit(1);

	print("after exit");
	assert( false );
}

