#!/usr/bin/env slang

import libs.CoreUtils.DF;


public void Main( int argc, string args )
{
	var cmd = new DF();

	cmd.Run( "-h" );
	// print( cmd.getExitCode() );

	foreach ( Line line : cmd ) {
		print( cast<string>( line ) );
	}

	print( "" );
	print( cmd[ 0 ] );
	print( cmd[ 3 ] );
}

