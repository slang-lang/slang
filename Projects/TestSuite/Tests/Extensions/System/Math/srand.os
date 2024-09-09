#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	print("TestCase 1: srand()");

	srand(time());

	int value = rand() % 100 + 1;

	print("rand() = " + value);

	return value > 0;
}

