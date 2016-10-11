#!/usr/local/bin/oscript

private int mNumber final;

public void Main(int argv = 0, string args = "") {
	mNumber = 1;

	assert( TestCase1() );
}

private bool TestCase1() modify {
/*
	int one const = 1;
	one = 2;	// throws ConstCorrectnessViolated exception
*/

	mNumber = 2;	// throws ConstCorrectnessViolated exception

	return false;
}

