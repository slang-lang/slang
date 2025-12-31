#!/usr/bin/env slang

import libs.CoreUtils.DU;


public void Main( int argc, string args )
{
	var cmd = new DU();

	cmd.Run( "-sch *" );

	foreach ( Line line : cmd ) {
		print( cast<string>( line ) );
	}

	// print( "" );
	// print( cmd[ 1 ] );
}

