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

		var reader = new JsonReader();
		var writer = new JsonStyledWriter();

		/*
		if ( params.contains( "string" ) ) {
			var data = reader.parse( params[ "string" ].Value );

			print( writer.toString( data ) );
			return;
		}
		*/

		foreach ( Parameter filename : params ) {
			print( writer.toString( reader.parse( new Scanner( filename.Key ).getText() ) ) );
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}

