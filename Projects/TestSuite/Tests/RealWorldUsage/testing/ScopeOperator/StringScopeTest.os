#!/usr/bin/env slang

import System.String;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1");

	print( "12345".Length() );
	print( "12345".CharAt(1) );
	//print( "12345".mValue );

	print( (string 123).Length() );

	return true;
}

