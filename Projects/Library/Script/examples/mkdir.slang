#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.mkdir( "test" );

	print( "ExitCode: " + cast<int>( result ) );
	print( "Output:   " + cast<string>( result ) );
}

