#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.mv( "test", "test2", "-v" );

	print( "Output:   " + cast<string>( result ) );
	print( "ExitCode: " + cast<int>( result ) );

	foreach ( Line line : result ) {
		print( cast<string>( line ) );
	}
}

