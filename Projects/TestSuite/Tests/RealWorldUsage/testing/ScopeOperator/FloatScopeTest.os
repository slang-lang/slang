#!/usr/local/bin/oscript

import System.Float;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1");

	print( 12345.678f.operator==(12345.f) );
	print( 12345.f.operator==(12345.f) );

	return true;
}

