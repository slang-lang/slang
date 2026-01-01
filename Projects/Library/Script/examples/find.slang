#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.find( ". -name ps.slang");

	foreach ( Line line : result ) {
		print( cast<string>( line ) );
	}
}

