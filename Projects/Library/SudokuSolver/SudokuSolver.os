#!/usr/bin/env slang

// Library imports
import libParam;
import FileReader;

// Project imports
import Board;


public int Main( int argc, string args ) {
	print( "Sudoku Solver v0.1.0" );

	var params = new ParameterHandler( argc, args );
	if ( params.empty() ) {
		print( "" );
		print( "Usage: program <filename>.board" );
		exit( -1 );
	}

	try {
		process( loadBoardFromFile( params[ 0 ].Key ) );
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return 0;
}

private Board loadBoardFromFile( string filename ) const {
	var it = new Scanner( filename ).getStringIterator( LINEBREAK );

	var board = new Board( 3, 3, 3 );

	int y = 1;
	while ( it.hasNext() ) {
		var line = it.next();

		for ( int x = 1; x <= strlen( line ); x++ ) {
			var value = cast<int>( substr( line, x - 1, 1 ) );
			
			board.set( x, y, value );
		}

		y++;
	}

	return board;
}

private void process( Board board ) {
	print( "" );
	print( board.toString() );
	print( "" );

	var startTime = time();

	board.calculatePossibleValues();

	var midTime = time();

	print( "Calculated possible values (in " + ( midTime - startTime ) + " seconds ):" );
	print( board.toString( true ) );
	print( "" );

	board.solve();

	var endTime = time();

	print( "" );
	print( "Solved in " + (endTime - midTime) + " seconds:" );
	print( board.toString() );
	print( "" );
}

