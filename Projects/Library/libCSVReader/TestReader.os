#!/usr/local/bin/slang

import libCSVReader.All;


public void Main( int argc, string args ) {
	try {
		var filename = "example.csv";

		print( "Processing file '" + filename + "'..." );

		var reader = new CSVReader( filename );

		print( cast<string>( reader.header() ) );
		print( cast<string>( reader[1] ) );
		print( cast<string>( reader[5] ) );
		print( cast<string>( reader[7] ) );
	}
	catch ( string e ) {
		print( e );
	}
	catch ( IException e ) {
		print( e.what() );
	}
}

