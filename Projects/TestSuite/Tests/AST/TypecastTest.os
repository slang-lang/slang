#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: basic typecast");

	int intValue = 173;

	// type cast from int to string
	string strValue = string intValue;

	return strValue == "173";
}

private bool TestCase2() {
	print("TestCase 2: extended typecast");

	string str = string 168 + 5;
	print("str = " + str);

	return str == "173";
}

