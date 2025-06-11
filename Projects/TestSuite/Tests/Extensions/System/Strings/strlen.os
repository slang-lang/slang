#!/usr/bin/env slang

import System.String;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: strlen()");

	string str = "This is a string";
	int length = strlen(str);
	print("strlen(str) = " + length);

	return length == 16;
}

private bool TestCase2() const {
	print("TestCase 2: String.Length()");

	String str = new String("This is a string");
	print("str.Length() = "+ str.Length());

	return str.Length() == 16;
}

