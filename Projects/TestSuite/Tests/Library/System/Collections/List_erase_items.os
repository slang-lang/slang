#!/usr/local/bin/slang

import System.Collections.List;

public void Main( int, string ) {
	assert( EraseFirstItem() );
	assert( EraseLastItem() );
	assert( EraseSecondLastItem() );
}

private bool EraseFirstItem() {
	print( "Erase first item from collection" );

	try {
	var collection = new List<int>();

	collection.push_back( 1 );
	collection.push_back( 2 );
	collection.push_back( 3 );

	assert( collection.size() == 3 );

	foreach ( int s : collection ) {
		print( "s: " + s );
	}

	print( "erase: " + collection[ collection.indexOf( 1 ) ] );
	collection.erase( collection.indexOf( 1 ) );

	assert( collection.size() == 2 );

	foreach ( int s : collection ) {
		print( "s: " + s );
	}

	return collection.indexOf( 1 ) == -1;
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

private bool EraseLastItem() {
	print( "Erase last item from collection" );

	var collection = new List<int>();

	collection.push_back( 1 );
	collection.push_back( 2 );
	collection.push_back( 3 );

	assert( collection.size() == 3 );

	foreach ( int s : collection ) {
		print( "s: " + s );
	}

	print( "erase: " + collection[ collection.indexOf( 3 ) ] );
	collection.erase( collection.indexOf( 3 ) );

	assert( collection.size() == 2 );

	foreach ( int s : collection ) {
		print( "s: " + s );
	}

	return collection.indexOf( 3 ) == -1;
}

private bool EraseSecondLastItem() {
	print( "Erase second last item from collection" );

	var collection = new List<int>();

	collection.push_back( 1 );
	collection.push_back( 2 );
	collection.push_back( 3 );

	assert( collection.size() == 3 );

	foreach ( int s : collection ) {
		print( "s: " + s );
	}

	print( "erase: " + collection[ collection.indexOf( 2 ) ] );
	collection.erase( collection.indexOf( 2 ) );

	assert( collection.size() == 2 );

	foreach ( int s : collection ) {
		print( "s: " + s );
	}

	return collection.indexOf( 2 ) == -1;
}

