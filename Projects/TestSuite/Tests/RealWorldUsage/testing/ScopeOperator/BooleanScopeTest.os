#!/usr/local/bin/slang

import System.Boolean;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1");

	print( false.operator==(true) );
	print( true.operator==(true) );

	return true;
}

