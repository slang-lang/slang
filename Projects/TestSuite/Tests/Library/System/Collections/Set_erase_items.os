#!/usr/bin/env slang

import System.Collections.Set;

public void Main( int, string ) {
	assert( EraseFirstItem() );
	assert( EraseLastItem() );
	assert( EraseSecondLastItem() );
}

private bool EraseFirstItem() {
	print( "Erase first item from set" );

	try {
	var set = new Set<int>();

	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );

	assert( set.size() == 3 );

	foreach ( int s : set ) {
		print( "s: " + s );
	}

	print( "erase: " + set[ set.indexOf( 1 ) ] );
	set.erase( set.indexOf( 1 ) );

	assert( set.size() == 2 );

	foreach ( int s : set ) {
		print( "s: " + s );
	}

	return set.indexOf( 1 ) == -1;
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

private bool EraseLastItem() {
	print( "Erase last item from set" );

	var set = new Set<int>();

	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );

	assert( set.size() == 3 );

	foreach ( int s : set ) {
		print( "s: " + s );
	}

	print( "erase: " + set[ set.indexOf( 3 ) ] );
	set.erase( set.indexOf( 3 ) );

	assert( set.size() == 2 );

	foreach ( int s : set ) {
		print( "s: " + s );
	}

	return set.indexOf( 3 ) == -1;
}

private bool EraseSecondLastItem() {
	print( "Erase second last item from set" );

	var set = new Set<int>();

	set.insert( 1 );
	set.insert( 2 );
	set.insert( 3 );

	assert( set.size() == 3 );

	foreach ( int s : set ) {
		print( "s: " + s );
	}

	print( "erase: " + set[ set.indexOf( 2 ) ] );
	set.erase( set.indexOf( 2 ) );

	assert( set.size() == 2 );

	foreach ( int s : set ) {
		print( "s: " + s );
	}

	return set.indexOf( 2 ) == -1;
}

