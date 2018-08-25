#!/usr/local/bin/oscript

import System.Collections.Range;


public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: basic Range test");

	foreach ( int i : new Range(1, 10) ) {
		print("i = " + i);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: Range test with step");

	foreach ( int i : new Range(1, 10, 3) ) {
		print("i = " + i);
	}

	return true;
}

