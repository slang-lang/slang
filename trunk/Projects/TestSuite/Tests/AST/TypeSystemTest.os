#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	//assert( TestCase5() );	// this should not work

	assert( TestCase11() );
	assert( TestCase12() );
	assert( TestCase13() );
	assert( TestCase14() );
	assert( TestCase15() );
	//assert( TestCase16() );	// this should not work
}

private bool TestCase1() {
	print("TestCase 1: <int> < <float>");

	int i = 1;
	float f = 2.1f;

	bool result = i < f;
	print("result = " + result);

	return result == true;
}

private bool TestCase2() {
	print("TestCase 2: int = <int> + <float>");

	int i = 1;
	float f = 2.1f;

	int result = i + f;
	print("result = " + result);

	return result == 3;
}

private bool TestCase3() {
	print("TestCase 3: float = <int> + <float>");

	int i = 1;
	float f = 2.1f;

	float result = i + f;
	print("result = " + result);

	return result == 3;
}

private bool TestCase4() {
	print("TestCase 4: float = (float <int> + <float>)");

	int i = 1;
	float f = 2.1f;

	float result = (float i) + f;
	print("result = " + result);

	return result == 3.1f;
}

private bool TestCase5() {
	print("TestCase 5: float = <float> + <int>");

	int i = 1;
	float f = 2.1f;

	float result = f + i;
	print("result = " + result);

	return result == 3.1f;
}

/*
private bool TestCase6() {
	print("TestCase 6: int = bool + bool");

	bool b1 = true;
	bool b2 = true;

	int result = b1 + b2;
	assert( !"this should not be possible" );
}
*/

private bool TestCase11() {
	print("TestCase 11: bool = ?");

	bool value;

	value = true;
	print("value = " + value);

	value = 1.71d;
	print("value = " + value);

	value = 1.389f;
	print("value = " + value);

	value = 664;
	print("value = " + value);

	value = "bla";
	print("value = " + value);

	return true;
}

private bool TestCase12() {
	print("TestCase 12: double = ?");

	double value;

	value = true;
	print("value = " + value);

	value = 1.73d;
	print("value = " + value);

	value = 1.389f;
	print("value = " + value);

	value = 664;
	print("value = " + value);

	return true;
}

private bool TestCase13() {
	print("TestCase 13: float = ?");

	float value;

	value = true;
	print("value = " + value);

	value = 1.73d;
	print("value = " + value);

	value = 1.389f;
	print("value = " + value);

	value = 664;
	print("value = " + value);

	// this is not supported
	//value = "bla";
	//print("value = " + value);

	return true;
}

private bool TestCase14() {
	print("TestCase 14: int = ?");

	int value;

	value = true;
	print("value = " + value);

	value = 1.73d;
	print("value = " + value);

	value = 1.389f;
	print("value = " + value);

	value = 664;
	print("value = " + value);

	// this is not supported
	//value = "bla";
	//print("value = " + value);

	return true;
}

private bool TestCase15() {
	print("TestCase 15: string = ?");

	string value;

	value = true;
	print("value = " + value);

	value = 1.73d;
	print("value = " + value);

	value = 1.389f;
	print("value = " + value);

	value = 664;
	print("value = " + value);

	value = "bla";
	print("value = " + value);

	return true;
}

/*
private bool TestCase16() {
	print("TestCase 16: void = ?");

	void value;

	value = true;
	print("value = " + value);

	value = 1.73d;
	print("value = " + value);

	value = 1.389f;
	print("value = " + value);

	value = 664;
	print("value = " + value);

	value = "bla";
	print("value = " + value);

	return false;
}
*/

