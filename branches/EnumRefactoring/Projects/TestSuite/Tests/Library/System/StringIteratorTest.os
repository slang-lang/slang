#!/usr/local/bin/oscript

import System.StringIterator;

public void Main(int argc = 0, string args = "") modify {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() modify {
	print("TestCase 1: valid iteration");

	StringIterator strIt = new StringIterator("This is a string", " ");

	int count;
	while ( strIt.hasNext() && count < 10 ) {
		string next = strIt.next();
		print("str.next() = " + next);

		count++;
	}

	return true;
}

private bool TestCase2() const {
	print("TestCase 2: valid iteration");

	StringIterator it = new StringIterator("This is a string", " ");

	int count;
	while ( it.hasNext() ) {
		print("str.current() = " + it.current());

		it.next();

		count++;
	}

	return true;
}

private bool TestCase3() const {
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

