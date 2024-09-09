#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: exp(double)");

	double value = 1.23d;

	print("exp(" + value + ") = " + exp(value));

	return exp(value) == 3.42123f;
}

private bool TestCase2() const {
	print("TestCase 2: exp(float)");

	float value = 1.23f;

	print("exp(" + value + ") = " + exp(value));

	return exp(value) == 3.42123f;
}

