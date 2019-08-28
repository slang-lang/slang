#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	assert( TestCase1() );
	//assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: simple recursion");

	return TestRecursion(10);
}

private bool TestCase2() const {
	print("TestCase 2: endless recursion, when will it crash?");

	endless(1);

	return false;
}

private bool TestRecursion(int value) {
	print("value = " + value);

	if ( value == 1 ) {
		return true;
	}

	value--;

	return TestRecursion(value);
}

private void endless(int count) {
	print("endless: " + count);

	endless(count + 1);
}

