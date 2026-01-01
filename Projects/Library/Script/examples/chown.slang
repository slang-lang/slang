#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.chown( "madelmann", "madelmann", "test" );

	print( "Output: " + cast<string>( result ) );
	print( "ExitCode: " + cast<int>( result ) );
}

