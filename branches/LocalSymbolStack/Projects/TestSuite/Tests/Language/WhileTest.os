#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2(5) );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1(int maxCount = 7) const {
	print("TestCase1");

	int count = 0;
	while ( count < maxCount ) {
		count = count + 1;
		print("count = " + count);
	}

	return count == maxCount;
}

private bool TestCase2(int maxCount = 7) const {
	print("TestCase2");

	int count = 0;

	int one = 1;
	print("one = " + one);

	while ( count < maxCount ) {
		count = count + 1;
		print("count = " + count);

		int one = 2;
		print("one = " + one);
	}

	print("one = " + one);

	return count == maxCount;
}

private bool TestCase3() const {
	print("TestCase3");

	int count = 0;

	while ( count < 5 ) {
		print("count = " + count);

		if ( count == 2 ) {
			break;
		}

		count = count + 1;
	}

	return count == 2;
}

private bool TestCase4() const {
	print("TestCase4");

	int count = 0;

	while ( count < 5 ) {
		print("count = " + count);
		count = count + 1;

		if ( count == 2 ) {
			continue;
		}
	}

	return true;
}

private bool TestCase5() const {
	print("TestCase5");

	int count = 0;

	while ( count < 5 ) {
		print("count = " + count);
		count = count + 1;

		if ( count == 2 ) {
			return true;
		}
	}

	return false;
}

