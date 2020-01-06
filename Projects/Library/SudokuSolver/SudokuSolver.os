#!/usr/local/bin/oscript

// Library imports

// Project imports
import Board;
import Cell;


public int Main(int argc, string args) {
	print( "Sudoku Solver v0.0.1" );

	try {
/*
		var board = new Board(9, 9);

		board.set(1, 1, 6);
		board.set(2, 1, 5);
		board.set(4, 1, 2);
		board.set(9, 1, 9);

		board.set(1, 2, 8);
		board.set(3, 2, 4);
*/

		var board = new Board(2, 2, 2);

		board.set(1, 1, 1);
		board.set(1, 3, 2);
		//board.set(2, 2, 3);
		board.set(2, 3, 1);
		board.set(3, 1, 2);
		board.set(4, 3, 4);
		board.set(1, 4, 3);

		print( "" );
		print( board.toString() );
		print( ""  );

/*
		assert( board.isSafe( 1, 1, 4 ) );
		assert( board.isUsedInBox( 0, 1, 2 ) );
		assert( ! board.isUsedInBox( 1, 1, 4) );
		assert( board.isUsedInLine( 3, 1 ) );
		assert( board.isUsedInRow( 3, 2 ) );
*/

		var cell = board.findEmptyCell();
		assert( cell && cell.X == 2 && cell.Y == 1 );

		board.calculatePossibleValues();

		print( "" );
		print( board.toString( true ) );
		print( "" );

		board.solve();
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return 0;
}

