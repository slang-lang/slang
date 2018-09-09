#!/usr/local/bin/oscript

import System.Collections.Range;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1");

	int count = 0;
	foreach ( int idx : 1..10 ) {
		print("idx = " + idx);

		count++;
	}

	return count == 10;
}

private bool TestCase2() {
	print("TestCase 2");

	try {
		print( (0..1).at(0) );
		assert( (0..1).at(0) == 0 );

		print( (0..1).at(1) );
		assert( (0..1).at(1) == 1 );

		print( (0..1).at(2) );
		assert( false );
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return (2..8).size() == 7;
}

