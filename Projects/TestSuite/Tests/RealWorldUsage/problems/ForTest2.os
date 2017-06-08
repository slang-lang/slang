#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	for ( int i = 0; /* empty coniditon clause */; i += 1 ) {
		if ( i > 4 )
			break;

		print("i = " + i);
	}
}

