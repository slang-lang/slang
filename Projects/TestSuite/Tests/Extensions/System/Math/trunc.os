#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: trunc(double)");

	double value = 1.5d;

	print("trunc(" + value + ") = " + trunc(value));

	return trunc(value) == 1.d;
}

private bool TestCase2() const {
	print("TestCase 2: trunc(float)");

	float value = 1.5f;

	print("trunc(" + value + ") = " + trunc(value));

	return trunc(value) == 1.f;
}

