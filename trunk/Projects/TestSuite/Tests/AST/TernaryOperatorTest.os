#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1() {
	print("TestCase 1: valid condition in ternary operator");

	int value = true ? 1 : 2;
	print("value = " + value);
	assert( value == 1 );

	return value == 1;
}

private bool TestCase2() {
	print("TestCase 2: invalid condition in ternary operator");

	int value = false ? 1 : 2;
	print("value = " + value);
	assert( value == 2 );

	return value == 2;
}

private bool TestCase3() {
	print("TestCase 3: cascaded ternary operator");

	int value = true ? false ? 1 : 3 : 2;
	print("value = " + value);
	assert( value == 3 );

	return value == 3;
}

private bool TestCase4() {
	print("TestCase 4: valid condition in short ternary operator");

	int value = 4 ?: 0;
	print("value = " + value);
	assert( value == 4 );

	return value == 4;
}

private bool TestCase5() {
	print("TestCase 5: invalid condition in short ternary operator");

	int value = 0 ?: 5;
	print("value = " + value);
	assert( value == 5 );

	return value == 5;
}

