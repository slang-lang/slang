#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.df( "-h" );

	foreach ( Line line : result ) {
		print( cast<string>( line ) );
	}

	print( "" );
	print( result[ 0 ] );
	print( result[ 3 ] );
}

