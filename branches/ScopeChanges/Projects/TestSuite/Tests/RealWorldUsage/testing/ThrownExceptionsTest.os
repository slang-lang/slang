#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	try {
		throw 1;

		try {
			throw "bla";
		}
		catch ( int e ) {
			print("e = " + e);
		}
	}
	catch ( int e ) {
		print("e = " + e);
	}
}

