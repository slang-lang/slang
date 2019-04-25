#!/usr/local/bin/oscript

import System.Exception;

public object NullPointerObject {
	public int Value;

	public string Length() {
		return "5";
	}
}

public void Main(int argc, string args) {
	NullPointerObject obj;

	try {
		print( "Length: " + obj.Length() );
	}
	catch ( NullPointerException e ) {
		assert( !"this does not work yet" );
		print("e = " + e.what());
	}
	catch ( string e ) {
		print("e = " + e );
	}

	try {
		print( "Value: " + obj.Value );
	}
	catch ( NullPointerException e ) {
		assert( !"this does not work yet" );
		print("e = " + e.what());
	}
	catch ( string e ) {
		print("e = " + e );
	}
}

