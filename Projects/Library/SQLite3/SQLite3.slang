#!/usr/bin/env slang

// library imports
import libParam;

// project imports
import libs.Consts;
import libs.Client;


public int Main( int argc, string args )
{
	try {
		var params = new ParameterHandler( argc, args );

		if ( params.contains( "help" ) ) {
			print( "usage: program [arg1 [arg2 [...] ] ]" );
			print( "" );
			return 0;
		}

		if ( params.contains( "version" ) ) {
			print( APPNAME + " " + VERSION );
			print( "" );
			return 0;
		}

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

