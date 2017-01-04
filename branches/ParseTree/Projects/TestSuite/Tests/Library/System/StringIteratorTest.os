#!/usr/local/bin/oscript

import System.StringIterator;

public void Main(int argc = 0, string args = "") modify {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() modify {
	print("TestCase 1: valid iteration");

	System.StringIterator strIt = new System.StringIterator("This is a string", " ");

	int count;

	while ( strIt.hasNext() && count < 10 ) {
		string next = strIt.next();
		print("str.next() = " + next);

		count++;
	}

	return true;
}

private bool TestCase2() const {
	print("TestCase 2: invalid iteration");

	System.StringIterator strIt = new System.StringIterator("This is a string", " ");

	try {
		int count;

		while ( count < 10 ) {
			string str = strIt.next();
			print("strIt.next() = " + str);

			count++;
		}

		assert(!"we should not get here!");
		return false;
	}
	catch {
		print("caught out of bounds exception");
		return true;
	}
}

