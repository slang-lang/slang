#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1: unary minus with integer literal");

	int result = -1;
	print("(" + result + ") == -(1)");

	return result == -(1);
}

private bool TestCase2() const {
	print("TestCase 2: unary minus with integer variable");

	int result = 5;
	print("" + result + " == -5");

	return -result == -5;
}

private bool TestCase3() const {
	print("TestCase 3: unary minues with expression");

	int result = -9;
	print("" + result + " == -(4 + 5)");

	return result == -(4 + 5);
}

