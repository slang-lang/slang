#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	//assert( TestCase3() );
	assert( TestCase4() );
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

/*
private bool TestCase3() {
	print("TestCase 3: cascaded ternary operator");

	int value = true ? false ? : 1 : 2;
	print("value = " + value);
	assert( value == 2 );

	return value == 2;
}
*/

private bool TestCase4() {
	print("TestCase 4: unequal ternary operator expressions");

	bool value = true ? 1 : false;
	print("value = " + value);

	assert( value == false );
	return value == false;
}

