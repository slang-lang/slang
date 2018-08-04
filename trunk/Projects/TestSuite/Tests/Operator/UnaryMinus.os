#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
}

private bool TestCase1() {
	print("TestCase 1: bool");

	bool value = -true;

	return true;
}

private bool TestCase2() {
	print("TestCase 2: double");

	double value = -1.d;

	return true;
}

private bool TestCase3() {
	print("TestCase 3: float");

	float value = -1.f;

	return true;
}

private bool TestCase4() {
	print("TestCase 4: int");

	int value = -1;

	return true;
}

private bool TestCase5() {
	print("TestCase 5: string");

	string value = -"text";

	return true;
}

private bool TestCase6() {
	print("TestCase 1: void");

	void value;

	return true;
}

