#!/usr/local/bin/slang

import System.Double;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1");

	print( 12345.678d.operator==(12345.d) );
	print( 12345.d.operator==(12345.d) );

	return true;
}

