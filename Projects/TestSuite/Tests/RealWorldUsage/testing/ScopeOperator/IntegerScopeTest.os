#!/usr/local/bin/slang

import System.Integer;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1");

	print( cast<string>( (12345).operator==(12345) ) );
	//print( 12345.mValue );

	print( cast<string>( (12345).operator+(12345) ) );

	return true;
}

