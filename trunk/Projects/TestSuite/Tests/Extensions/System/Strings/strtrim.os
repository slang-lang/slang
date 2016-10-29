#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: strtrim()");

	string value = "   trim   ";
	print("strtrim(\"" + value + "\") = \"" + strtrim(value) + "\"");

	return strtrim(value) == "trim";
}

