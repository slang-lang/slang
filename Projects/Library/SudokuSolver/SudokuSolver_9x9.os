#!/usr/local/bin/slang

// Library imports

// Project imports
import Board;
import Cell;


public int Main(int argc, string args) {
	print( "Sudoku Solver v0.0.1" );

	try {
		var board = new Board( 3, 3, 3 );
		board.set(2, 1, 4);
		board.set(3, 1, 7);
		board.set(7, 1, 9);
		board.set(8, 1, 1);

		board.set(5, 2, 1);

		board.set(1, 3, 3);
		board.set(5, 3, 4);
		board.set(9, 3, 2);

		board.set(2, 4, 2);
		board.set(3, 4, 3);
		board.set(4, 4, 7);
		board.set(6, 4, 1);
		board.set(7, 4, 8);
		board.set(8, 4, 9);

		board.set(1, 5, 8);
		board.set(9, 5, 7);

		board.set(1, 6, 7);
		board.set(9, 6, 5);

		board.set(2, 7, 7);
		board.set(4, 7, 8);
		board.set(5, 7, 3);
		board.set(6, 7, 6);
		board.set(8, 7, 2);
		board.set(9, 7, 1);

		board.set(1, 8, 1);
		board.set(3, 8, 2);
		board.set(4, 8, 9);
		board.set(5, 8, 7);
		board.set(6, 8, 5);
		board.set(9, 8, 3);

		board.set(2, 9, 3);
		board.set(4, 9, 1);
		board.set(5, 9, 2);
		board.set(6, 9, 4);
		board.set(9, 9, 9);

		print( "Start:" );
		print( board.toString() );
		print( "" );

		board.calculatePossibleValues();

		print( "Calculated possible values:" );
		print( board.toString( true ) );
		print( "" );

		var startTime = time();
		board.solve();
		var endTime = time();

		print( "" );
		print( "Solved in " + (endTime - startTime) + " seconds:" );
		print( board.toString() );
		print( "" );
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return 0;
}

