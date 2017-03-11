#!/usr/local/bin/oscript

import System.String;

public void Main(int argc = 1, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() throws {
	print("AST: try-catch-finally");

	try {
		print("try");

		throw new string("this is an exception");
	}
	catch ( int e ) {
		print("catch(int): " + e);

		assert( false );
	}
	catch ( string e ) {
		print("catch(string): " + e);

		return true;
	}
	finally {
		print("finally");
	}

	assert( !"after return" );
	return false;
}

