#!/usr/local/bin/oscript

import System.Collections.Range;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	//assert( TestCase7() );	// functions are currently not supported
}

private bool TestCase1() {
	print("TestCase 1: basic range operator with literals");

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
		//print( (0..1)[0] );
		//assert( (0..1)[0] == 0 );

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

private bool TestCase3() {
	print("TestCase 3: range with <int variable>..<int literal>");

	int x = 1;

	int count = 0;
	foreach ( int idx : x..10 ) {
		print("idx = " + idx);

		count++;
	}

	return count == 10;
}

private bool TestCase4() {
	print("TestCase 4: range with <int literal>..<int variable>");

	int y = 10;

	int count = 0;
	foreach ( int idx : 1..y ) {
		print("idx = " + idx);

		count++;
	}

	return count == 10;
}

private bool TestCase5() {
	print("TestCase 5: range with <int variable>..<int variable>");

	int x = 1;
	int y = 10;

	int count = 0;
	foreach ( int idx : x..y ) {
		print("idx = " + idx);

		count++;
	}

	return count == 10;
}

private bool TestCase6() {
	print("TestCase 6: range with constant");

	int x const = 1;
	int y const = 10;

	int count = 0;
	foreach ( int idx : x..y ) {
		print("idx = " + idx);

		count++;
	}

	return count == 10;
}

/*
private bool TestCase7() {
	print("TestCase 7: range with function");

	int count = 0;
	for ( int idx : get1() .. get10() ) {
		print("idx = " + idx);

		count++;
	}

	return count == 10;
}

private int get1() { return 1; }
private int get10() { return 10; }

*/

/*
private bool TestCase8() {
	print("TestCase 8: failing");

	int x = 1;
	float y = 10.f;

	int count = 0;
	foreach ( int idx : x..y ) {
		print("idx = " + idx);

		count++;
	}

	return false;
}
*/

