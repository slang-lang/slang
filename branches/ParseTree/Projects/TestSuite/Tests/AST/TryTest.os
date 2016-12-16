#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	try {
		print("try");

		return;

		throw new int(42);
	}
/*
	catch ( string e ) {
		print(e);
	}
*/
	finally {
		print("finally");
	}

	assert( !"after return" );
}

