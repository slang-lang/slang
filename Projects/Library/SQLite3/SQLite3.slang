#!/usr/bin/env slang

// library imports
import libParam;

// project imports
import Client;


public int Main( int argc, string args )
{
	try {
		var params = new ParameterHandler( argc, args );

		string filename;
		if ( !params.empty() ) {
			filename = params[ 0 ].Key;
		}

		return ( new Client( filename ) ).Run();
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return -1;
}

