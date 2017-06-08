#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: unequal ternary operator expressions");

	bool value = true ? 1 : false;
	print("value = " + value);

	assert( value == false );
	return value == false;
}

