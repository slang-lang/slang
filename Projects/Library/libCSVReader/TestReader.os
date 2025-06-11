#!/usr/bin/env slang

import libCSVReader;


public void Main( int argc, string args ) {
	try {
		var filename = "example_small.csv";

		print( "Processing file '" + filename + "'..." );

		var reader = new CSVReader( filename );

		foreach ( DataEntry row : reader ) {
			print( cast<string>( row ) );
		}

		print( cast<string>( reader.header() ) );
		print( cast<string>( reader[1] ) );
		print( cast<string>( reader[5] ) );
		print( cast<string>( reader[7] ) );
		print( cast<string>( reader[100] ) );
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}
