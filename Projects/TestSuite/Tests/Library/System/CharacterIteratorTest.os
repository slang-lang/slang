#!/usr/local/bin/slang

import System.CharacterIterator;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: iterate");

	string source = "This is a string";
	string target;

	var it = new CharacterIterator(source);

	while ( it.hasNext() ) {
		it.next();

		string c = it.current();
		target += c;

		write(c);
	}
	writeln();

	print("'" + source + "' == '" + target + "'");

	return source == target;
}

private bool TestCase2() {
	print("TestCase 2: for-loop");

	string source = "This is a string";
	string target;

	for ( var it = new CharacterIterator(source); it.hasNext(); ) {
		it.next();

		target += it.current();

		write(it.current());
	}
	writeln();

	print("'" + source + "' == '" + target + "'");

	return source == target;
}

