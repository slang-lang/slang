#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.du( "-sch *" );

	foreach ( Line line : result ) {
		print( cast<string>( line ) );
	}

	// print( "" );
	// print( result[ 1 ] );
}

