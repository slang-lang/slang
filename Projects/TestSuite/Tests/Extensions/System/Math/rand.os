#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	print("TestCase 1: rand()");

	int value = rand() % 10 + 1;

	print("rand() = " + value);

	return value > 0;
}

