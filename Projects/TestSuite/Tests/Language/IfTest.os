#!/usr/local/bin/slang

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() {
	print("TestCase 1");

	int one = 1;
	print("one = " + one);

	if ( true ) {
		int one = 2;
		print("one = " + one);

		print("TestCase1: true");
	}

	if ( false ) {
		print("TestCase1: false");
		assert(false);
	}

	return true;
}

private bool TestCase2(int param1 = 2) {
	print("TestCase 2 (param1 = " + param1 + ")");

	int one = 0;
	print("one = " + one);

	if ( (param1 - 1) == 0 ) {
		print("TestCase2: if-true");
		assert(false);
	}
	else if ( (param1 - 2) == 0 ) {
		int one = 1;
		print("one = " + one);

		print("TestCase2: else-if-true");
	}
	else {
		print("TestCase2: else-if-else");
		assert(false);
	}

	print("one = " + one);
	assert(one == 0);

	one = one + 1;
	print("one = " + one);
	assert( one == 1 );
	return true;
}

private bool TestCase3() {
	print("TestCase 3");

	// comparison operators are stickier than boolean operators
	if ( true == true && false == false ) {
		print("TestCase3: true");
		return true;
	}

	print("TestCase3: false");
	assert(false);
	return false;
}

private bool TestCase4() {
	print("TestCase 4");

	// comparison operators are stickier than boolean operators but parenthesis are even better :-)
	if ( true == (true && false) == false ) {
		print("TestCase4: true");
		return true;
	}

	print("TestCase4: false");
	assert(false);
	return false;
}

