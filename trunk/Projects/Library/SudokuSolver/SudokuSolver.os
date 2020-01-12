#!/usr/local/bin/oscript

// Library imports

// Project imports
import Board;
import Cell;


public int Main(int argc, string args) {
	print( "Sudoku Solver v0.0.1" );

	try {

		var board = new Board(2, 2, 2);

		board.set(1, 1, 1, true);
		//board.set(2, 1, 2, true);
		//board.set(2, 2, 4, true);
		//board.set(3, 1, 3, true);
		//board.set(3, 3, 4, true);
		//board.set(4, 4, 1, true);


/*
		var board = new Board( 3, 3, 2 );
		board.set(1, 1, 6);
		board.set(6, 1, 4);
		board.set(3, 2, 3);
		board.set(2, 3, 2);
		board.set(4, 5, 2)
		board.set(1, 6, 2);
		board.set(6, 6, 2);
*/


		print( "Start:" );
		print( board.toString() );
		print( "" );

/*
		assert( board.isSafe( 1, 1, 4 ) );
		assert( board.isUsedInBox( 0, 1, 2 ) );
		assert( ! board.isUsedInBox( 1, 1, 4) );
		assert( board.isUsedInLine( 3, 1 ) );
		assert( board.isUsedInRow( 3, 2 ) );

		var cell = board.findEmptyCell();
		assert( cell && cell.X == 2 && cell.Y == 1 );
*/

		board.calculatePossibleValues();

		print( "Calculated possible values:" );
		print( board.toString( /*true*/ ) );
		print( "" );

		print( "Start time: " + time() );

		board.solve();

		print( "End time: " + time() );

		print( "Solved:" );
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

