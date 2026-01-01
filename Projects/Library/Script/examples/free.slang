#!/usr/bin/env slang

import libs.Utils;


public void Main( int argc, string args )
{
	// var result = Utils.free();

	foreach ( Line line : Utils.free() ) {
		print( cast<string>( line ) );
	}
}

