#!/usr/local/bin/slang

public void Main(int argc = 1, string args = "") {
	for ( int i = 0; i < 5; i += 1 ) {
		print("i = " + i);
	}
	print("done(1)");

	for ( int j = 0; j < 5; j += 1 )
		print("j = " + j);
	print("done(2)");
}

