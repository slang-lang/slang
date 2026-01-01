#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.chmod( "o-x", "test" );

	print( "Output: " + cast<string>( result ) );
	print( "ExitCode: " + cast<int>( result ) );
}

