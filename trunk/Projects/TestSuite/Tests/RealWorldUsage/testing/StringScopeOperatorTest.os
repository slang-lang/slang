#!/usr/local/bin/oscript

import System.String;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1");

	print( "12345".Length() );

	return true;
}

