#!/usr/local/bin/slang

import System.String;

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() const {
	print("TestCase 1: strftime()");

	print( strftime( "%c %Z" ) );
	print( strftime( "%Y-%m-%d %H:%M:%S" ) );

	return true;
}

