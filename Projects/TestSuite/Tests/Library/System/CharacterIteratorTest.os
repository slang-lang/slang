#!/usr/local/bin/oscript

import System.CharacterIterator;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: iterate");

	int count;
	string source = "This is a string";
	string target;

	CharacterIterator it = new CharacterIterator(source);

	while ( it.hasNext() ) {
		count++;

		string c = it.current();
		target += c;

		write(c);

		it.next();
	}
	writeln("");

	//print("'" + source + "' == '" + target + "'");

	assert(count == strlen(source));
	return source == target;
}

private bool TestCase2() {
	print("TestCase 2: for loop");

	int count;
	string source = "This is a string";
	string target;

	for ( CharacterIterator it = new CharacterIterator(source); it.hasNext(); it++ ) {
		count++;

		target += it.current();

		write(it.current());
	}
	writeln("");

	//print("'" + source + "' == '" + target + "'");

	assert( count == strlen(source) );
	return source == target;
}

