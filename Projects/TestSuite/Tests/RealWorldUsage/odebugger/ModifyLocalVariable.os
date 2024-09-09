#!/usr/local/bin/slang

public void Main(int argc, string args) {
	string str = "bla";

	if ( str != "bla" ) {
		print("slang-dbg changed str from 'bla' to '" + str + "'.");
	}
	else {
		print("nothing happened.");
	}
}

