#!/usr/bin/env slang

import System.Collections.Iterator;
import System.Collections.List;
import System.String;

public void Main( int arc, string args ) {
	print( "Filling collection" );

	var collection = new List<int>();

	for ( int i = 0; i < 1000; i++ ) {
		collection.push_back( i );
	}

	var start = time();
	print( "Iterate over collection: " + start );

	var it = collection.getIterator();
	while ( it.hasNext() ) {
		//it.next();
		print( it.next() );
	}

	var end = time();
	print( "Finished iterating: " + end );

	print( "Took " + (end - start) + " seconds" );
}

