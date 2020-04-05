#!/usr/local/bin/oscript

// Library imports

// Project imports
import Board;
import Cell;


public int Main(int argc, string args) {
	print( "Sudoku Solver v0.0.1" );

	try {
/*
		var board = new Board(2, 2, 2);

		board.set(1, 1, 1, true);
		board.set(2, 1, 2, true);
		board.set(2, 2, 4, true);
		board.set(3, 1, 3, true);
		board.set(3, 3, 4, true);
		//board.set(4, 4, 1, true);
*/

		var board = new Board( 3, 3, 2 );
		board.set(1, 1, 6);
		board.set(6, 1, 4);
		board.set(3, 2, 3);
		board.set(2, 3, 2);
		board.set(5, 4, 2)
		board.set(1, 6, 2);
		board.set(6, 6, 2);

/*
		var board = new Board( 3, 3, 3 );
		board.set(1, 1, 9);
		board.set(2, 1, 7);
		board.set(4, 1, 1);
		board.set(9, 1, 5);
		board.set(3, 2, 5);
		board.set(5, 2, 9);
		board.set(7, 2, 2);
		board.set(9, 2, 1);
		board.set(1, 3, 8);
		board.set(5, 3, 4);
		board.set(5, 4, 8);
		board.set(4, 5, 7);
		board.set(5, 6, 2);
		board.set(6, 6, 6);
		board.set(9, 6, 9);
		board.set(1, 7, 2);
		board.set(4, 7, 3);
		board.set(9, 7, 6);
		board.set(4, 8, 2);
		board.set(7, 8, 9);
		board.set(3, 9, 1);
		board.set(4, 9, 9);
		board.set(6, 9, 4);
		board.set(7, 9, 5);
		board.set(8, 9, 7);
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

