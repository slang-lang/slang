#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") throws {
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

		return;
	}
	finally {
		print("finally");

		assert( !"after return" );
	}

	assert( !"after return" );
}

