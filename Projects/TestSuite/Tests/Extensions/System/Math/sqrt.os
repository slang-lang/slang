#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: sqrt(double)");

	double value = 9.d;

	print("sqrt(" + value + ") = " + sqrt(value));

	return sqrt(value) == 3.d;
}

private bool TestCase2() const {
	print("TestCase 2: sqrt(float)");

	float value = 9.f;

	print("sqrt(" + value + ") = " + sqrt(value));

	return sqrt(value) == 3.f;
}

