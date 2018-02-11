#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	for ( int i = 0; i < 5; i += 1 ) {
		print("i = " + i);
	}

	for ( int j = 0; j < 5; j++ ) {
		print("j = " + j);
	}

	for ( int k = 0; k < 5; { print("k = " + k); k += 1; } ) {
		print("k = " + k);
	}

	for ( int l = 0; l < 5; ) {
		print("l = " + l);
		l++;
	}

	int m = 0;
	for ( ; m < 5; ) {
		print("m = " + m);
		m++;
	}

	int n = 0;
	for ( ; ; { print("n = " + n); n++; if ( n >= 5 ) { break; } } )
		;
}

