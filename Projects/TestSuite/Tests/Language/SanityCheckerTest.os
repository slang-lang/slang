#!/usr/bin/env slang

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	{
		int one = 1;

	return false;
}

private bool TestCase2() const {
	assert( true;

	return false;
}

private bool TestCase3() const {
	string bla = "bla bla;

	return false;
}

