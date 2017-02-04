#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	for ( int i = 0; i < 5; i += 1 ) {
		if ( i > 2 )
			break;

		print("i = " + i);
	}
}

