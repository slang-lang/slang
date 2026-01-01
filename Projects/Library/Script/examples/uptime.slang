#!/usr/bin/env slang

import libs.Utils;


public void Main( int argc, string args )
{
	// var result = Utils.uptime();

	foreach ( Line line : Utils.uptime() ) {
		print( cast<string>( line ) );
	}
}

