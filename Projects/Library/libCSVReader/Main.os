#!/usr/local/bin/slang

import libCSVReader;
import libParam;


public void Main( int argc, string args ) {
	if ( argc < 2 ) {
		print( "usage: program [arg1 [arg2 [...] ] ]" );
		print( "" );
		return;
	}

	try {
		var params = new ParameterHandler( argc, args );

		foreach ( Parameter filename : params ) {
			if ( params.size() > 1 ) {
				print( filename.Key + ":" );
			}

			var reader = new CSVReader( filename.Key );

    		foreach ( DataEntry row : reader ) {
    			print( cast<string>( row ) );
    		}
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}
