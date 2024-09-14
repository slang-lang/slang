#!/usr/local/bin/slang

import System.StringIterator;

public void Main(int argc = 0, string args = "") modify {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() {
	print("TestCase 1: valid iteration");

	StringIterator strIt = new StringIterator("This is a string", " ");

	int count;
	while ( strIt.hasNext() && count < 10 ) {
		print("str.next() = " + strIt.next());

		count++;
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: valid iteration");

	StringIterator it = new StringIterator("This is a string", " ");

	int count;
	while ( it.hasNext() ) {
		it.next();
		print("str.current() = " + it.current());

		count++;
	}

	return true;
}

private bool TestCase3() {
	print("TestCase 3: invalid iteration");

	StringIterator strIt = new StringIterator("This is a string", " ");

	try {
		int count;

		while ( count < 10 ) {
			string str = strIt.next();
			print("strIt.next() = " + str);

			count++;
		}

		assert(!"we should not get here!");
	}
	catch ( OutOfBoundsException e ) {
		print("e.what(): " + e.what());

		return true;
	}
	catch {
		print("caught unknown exception!");
		assert(!"we should not get here!");
	}

	return false;
}

private bool TestCase4() {
	print("TestCase 4: valid iteration with separator change");

	StringIterator it = new StringIterator("This is a string", " ");

	try {
		string value;

		assert( it.hasNext() );

		value = it.next();
		print("value = '" + value + "'");
		assert( value == "This" );

		value = it.next("i");
		print("value = '" + value + "'");
		assert( value == "s a str" );

		value = it.next();
		print("value = '" + value + "'");
		assert( value == "ng" );

		return true;
	}
	catch ( IException e ) {
		print("e.what(): " + e.what());

		return false;
	}

	return false;
}

