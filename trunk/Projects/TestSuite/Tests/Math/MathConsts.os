#!/usr/local/bin/oscript

import System.Math.Consts;


public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("Math.Consts.E");

	var e = Math.Consts.E;
	assert( typeid(e) == "double" );

	print("Math.Consts.E = " + e);

	return true;
}

private bool TestCase2() {
	print("Math.Consts.PI");

	var pi = Math.Consts.PI;
	assert( typeid(pi) == "double" );

	print("Math.Consts.PI = " + pi);

	return true;
}


