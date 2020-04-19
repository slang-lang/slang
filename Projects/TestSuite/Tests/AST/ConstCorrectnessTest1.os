#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	int i const = 1;
	print("i = " + i);
	assert( i == 1 );

	i = 2;
	print("i = " + i);
	assert( false );
}

