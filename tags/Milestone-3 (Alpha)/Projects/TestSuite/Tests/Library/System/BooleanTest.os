#!/usr/local/bin/oscript

import System.Boolean;

public void Main(int argc = 0, string args = "") modify {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1: unary not");

	// default value is false
	Boolean value;// = new Boolean();

	print("value = " + (!value)!);

	return (!value)!;	// this is a really crazy test..
}

private bool TestCase2() const {
	print("TestCase 2: automatic type convertion");

	Boolean value = new Boolean(true);
	print(string value);

	return bool value;
}

private bool TestCase3() modify {
	print("TestCase 3: Boolean.operator=()");

	Boolean value = new Boolean();
	value = bool "foo bar";
	print(string value);
	assert(bool value);

	return true;
}

