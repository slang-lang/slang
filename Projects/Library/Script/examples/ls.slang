#!/usr/bin/env slang

import libs.CoreUtils.LS;


public void Main( int argc, string args )
{
	var cmd = new LS();

	cmd.Run( "-la *" );

	foreach ( Line line : cmd ) {
		print( cast<string>( line ) );
	}

	print( "" );
	print( cmd[ 1 ] );
}

