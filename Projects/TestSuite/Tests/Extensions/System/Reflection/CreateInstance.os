#!/usr/local/bin/slang

import System.String;

public void Main(int argc, string args) {
	var str = String createInstance("String");

	assert( str );
	assert( str is Object );
	assert( str is String );

	str = "This is a test";

	print( cast<string>(str) );
}

