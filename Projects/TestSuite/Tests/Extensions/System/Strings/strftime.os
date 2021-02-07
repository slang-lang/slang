#!/usr/local/bin/slang

import System.String;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: strftime()");

	print( strftime( "%c %Z" ) );
	print( strftime( "%Y-%m-%d %H:%M:%S" ) );

	return true;
}

private bool TestCase2() const {
	print("TestCase 2: strftime with time parameter");

	var time = time() - 100;

	print( strftime( "%c %Z", time ) );
	print( strftime( "%Y-%m-%d %H:%M:%S", time ) );

	return true;
}

