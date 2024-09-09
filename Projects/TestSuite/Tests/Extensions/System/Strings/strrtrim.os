#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: strrtrim()");

	string value = "   right trim   ";
	print("strrtrim(\"" + value + "\") = \"" + strrtrim(value) + "\"");

	return strrtrim(value) == "   right trim";
}

