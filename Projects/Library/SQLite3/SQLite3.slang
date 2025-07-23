#!/usr/bin/env slang

// library imports
import libParam;

// project imports
import Client;


public void Main( int argc, string args )
{
	if ( argc < 2 ) {
		print( "usage: program [arg1 [arg2 [...] ] ]" );
		print( "" );
		return;
	}

	try {
		var params = new ParameterHandler( argc, args );

		var client = new Client( params[ 0 ].Key );
		client.Run();
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}

