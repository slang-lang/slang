#!/usr/bin/env slang

import libs.CoreUtils.UPTIME;


public void Main( int argc, string args )
{
	var cmd = new UPTIME();

	print( cmd.Run() );

	foreach ( Line line : cmd ) {
		print( cast<string>( line ) );
	}
}

