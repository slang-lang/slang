#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: shift left (<<)");

	string ab = "a" << "b";

	return ab == "ab";
}

private bool TestCase2() {
	print("TestCase 2: shift right (>>)");

	string ab = "a" >> "b";

	return ab == "ab";
}
