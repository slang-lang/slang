#!/usr/bin/env slang

import libs.Files;


public void Main( int argc, string args )
{
	var result = Files.cat( "ps.slang" );

	print( cast<string>( result ) );
}

