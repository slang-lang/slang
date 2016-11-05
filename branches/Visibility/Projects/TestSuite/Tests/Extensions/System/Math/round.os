#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: round(double)");

	double value = 1.5d;

	print("round(" + value + ") = " + round(value));

	return round(value) == 2.d;
}

private bool TestCase2() const {
	print("TestCase 2: round(float)");

	float value = 1.49f;

	print("round(" + value + ") = " + round(value));

	return round(value) == 1.f;
}

