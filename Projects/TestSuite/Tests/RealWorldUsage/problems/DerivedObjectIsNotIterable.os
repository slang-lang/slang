#!/usr/local/bin/slang

import System.Collections.Vector;

public object DerivedVector extends Vector<int> {
	public void Constructor() {
		base.Constructor();
	}
}

public void Main( int argc, string args ) {
try {
	var collection = new DerivedVector();

	collection.push_back( 1 );

	foreach( int i : collection ) {
		print( "i = " + i );
	}
}
catch ( string e ) {
	print( "Exception: " + e );
}
catch ( IException e ) {
	print( "Exception: " + e.what() );
}
catch ( Exception e ) {
	print( "Exception: " + e.what() );
}
}

