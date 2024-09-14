#!/usr/local/bin/slang

// THIS WILL FAIL

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	int i = 0;

	i = incStaticVar();
	print("i = " + i);

	i = incStaticVar();
	print("i = " + i);

	i = incStaticVar();
	print("i = " + i);

	return i == 3;
}

private int incStaticVar() {
	static int val = 0;

	val = val + 1;

	return val;
}

