#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() const {
	writeln("TestCase1: exit");

	exit(0);

	assert(!"this should not happen");
}

