#!/usr/local/bin/oscript

import System.Double;

public void Main(int argc = 0, string args = "") modify {
	assert( TestCase1() );
	//assert( TestCase2() );

	//assert(!"not implemented");
}

private bool TestCase1() modify {
	print("TestCase 1: Double");

	Double value = new Double();

	assert( !value.Value() );

	value.Value(double 1);
	assert( value.Value() );
	//assert( bool value );

	return true;
}

private bool TestCase2() const {
	print("TestCase 2");

	assert( false );
	return false;
}

