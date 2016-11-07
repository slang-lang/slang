#!/usr/local/bin/oscript

import System.Collections.List;
import System.String;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	//assert( TestCase3() );
}

private bool TestCase1() {
	print("TestCase 1: valid foreach with collection");

	System.List list = new System.List();

	list.push_back(Object new String("664"));
	list.push_back(Object new String("173"));
	list.push_back(Object new String("1389"));

	assert( list.size() == 3 );

	//foreach ( list => Object s ) 

	foreach ( Object s : list ) {
		print(string s);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: valid foreach with collection");

	System.List list = new System.List();

	list.push_back(Object new String("664"));
	list.push_back(Object new String("173"));
	list.push_back(Object new String("1389"));

	assert( list.size() == 3 );

	foreach ( Object r : list ) {
		foreach ( Object s : list ) {
			foreach ( Object t : list ) {
				print(string r);
				print(string s);
				print(string t);
			}
		}
	}

	return true;
}

private bool TestCase3() {
	print("TestCase 3: invalid foreach");

	String str = new String("this is no collection");

	foreach ( String s : str ) {
		assert(false);
	}

	return false;
}
