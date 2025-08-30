#!/usr/bin/env slang

// Library imports
import libParam;
import System.IO.File;

// Project imports

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

			readFile( filename.Key );
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}

private void readFile( string filename ) const {
	var file = new System.IO.File( filename, System.IO.File.AccessMode.ReadOnly );

	print( file.readString( file.getSize() ) );
}
