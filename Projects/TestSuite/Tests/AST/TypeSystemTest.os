#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() {
	print("TestCase 1: int < float");

	int i = 1;
	float f = 2.1f;

	bool result = i < f;
	print("result = " + result);

	return result == true;
}

private bool TestCase2() {
	print("TestCase 2: int = int + float");

	int i = 1;
	float f = 2.1f;

	int result = i + f;
	print("result = " + result);

	return result == 3;
}

private bool TestCase3() {
	print("TestCase 3: float = int + float");

	int i = 1;
	float f = 2.1f;

	float result = i + f;
	print("result = " + result);

	return result == 3;
}

private bool TestCase4() {
	print("TestCase 4: float = float + int");

	int i = 1;
	float f = 2.1f;

	float result = f + i;
	print("result = " + result);

	return result == 3.1f;
}

