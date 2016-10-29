#!/usr/local/bin/oscript

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
	int var static = 0;

	var = var + 1;

	return var;
}

