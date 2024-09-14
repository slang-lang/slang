#!/usr/local/bin/slang

public void Main(int argc, string argv) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase1()");
}

private bool TestCase2() const {
	print("TestCase2()");
	return;
}

