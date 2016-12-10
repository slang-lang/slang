#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1");

	if ( true || false ) {
		print("true || false => if-block");
	}
	else {
		assert(false);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2");

	if ( true || WriteFalse() ) {
		print("true || false => if-block");
	}
	else {
		assert(false);
	}

	return true;
}

private bool WriteFalse() {
	print("print: false");

	assert(false);
}

