#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	if ( true ) {
		print("if");
	}
	else {
		print("else");
		assert( false );
	}

	if ( 173 >= 1389 ) {
		print("if");
		assert( false );
	}
	else if ( true ) {
		print("else if");
	}

	if ( true ) {
		print("if");
	}
}

