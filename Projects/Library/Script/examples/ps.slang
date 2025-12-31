#!/usr/bin/env slang

import libs.CoreUtils.PS;


public void Main( int argc, string args )
{
	var cmd = new PS();

	cmd.Run( "aux | grep $(whoami)" );
	// print( cmd.getExitCode() );

	foreach ( Line line : cmd ) {
		print( cast<string>( line ) );
	}

	print( "" );
	// print( cmd[ 1 ] );
}

