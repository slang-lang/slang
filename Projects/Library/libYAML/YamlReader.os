#!/usr/local/bin/slang

// Library imports
import FileReader;
//import libJson;
import libParam;

// Project imports
import Reader;

public void Main( int argc, string args ) {
	if ( argc < 2 ) {
		print( "usage: program [arg1 [arg2 [...] ] ]" );
		print( "" );
		return;
	}

	try {
		var params = new ParameterHandler( argc, args );

		foreach ( Parameter filename : params ) {
			if ( params.size() > 2 ) {
				print( filename.Key + ":" );
			}
	
			var reader = new YamlReader();

			print( "parsing..." );

			var data = reader.parse( new Scanner( filename.Key ).getText() );
	
			print( "done parsing." );

			print( data.toString() );

			print( "done." );
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}

