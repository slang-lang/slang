#!/usr/bin/env slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: shift left (<<)");

	string ab = "a" << "b";

	return ab == "ab";
}
