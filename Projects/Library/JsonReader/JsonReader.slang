#!/usr/bin/env slang

// Library imports
import FileReader;
import libJson;
import libParam;

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

			var reader = new JsonReader();
			var data = reader.parse( new Scanner( filename.Key ).getText() );

			var writer = new JsonStyledWriter();
			print( writer.toString( data ) );
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}

