#!/usr/local/bin/oscript

import System.Character;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() {
	print("TestCase 1: length restriction");

	Character c = new Character("this should only hold the first character");
	print("c = " + string c);

	return strlen(string c) == 1;
}

private bool TestCase2() {
	print("TestCase 2: invalid input length");

	try {
		Character c = new Character("this is too long", true);
	}
	catch ( InvalidLengthException e ) {
		print("InvalidLengthException e.what() = " + e.what());
		return true;
	}

	return false;
}

private bool TestCase3() {
	print("TestCase 3: compare operators");

	Character c = new Character("b");

	print("c == \"b\": " + (c == "b"));
	assert( c == "b" );

	print("c == new Character(\"b\"): " + (c == new Character("b")));
	assert( c == new Character("b") );

	return true;
}

