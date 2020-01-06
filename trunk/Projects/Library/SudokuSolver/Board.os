
// Library imports
import System.Collections.Map;
import System.Collections.Range;

// Project imports
import Cell;


public object Board {
	public void Constructor(int sizeX, int sizeY, int repeat) {
		Cells = new Map<string, Cell>();
		Repeat = repeat;
		SizeX = sizeX;
		SizeY = sizeY;

		foreach ( int y : 1..SizeY * Repeat ) {
			foreach ( int x : 1..SizeX * Repeat ) {
				Cells.insert( cast<string>( x ) + cast<string>( y ), new Cell(x, y) );
			}
		}
	}

	public Board Copy() const {
		var result = new Board();

		result.Cells = copy Cells;
		result.Repeat = Repeat;
		result.SizeX = SizeX;
		result.SizeY = SizeY;

		return result;
	}

	public void calculatePossibleValues() modify {
		bool recalculate = false;

		while ( true )
		{
		try {
		foreach ( int y : 1..SizeY * Repeat ) {
			foreach ( int x : 1..SizeX * Repeat ) {
				var cell = Cells.get( cast<string>( x ) + cast<string>( y ) );

				if ( cell.Value == 0 ) {
					cell.PossibleValues.clear();

					foreach ( int value : 1..SizeX * Repeat ) {
						if ( isSafe( x, y, value ) ) {
							cell.PossibleValues.push_back( value );
						}
					}
				}

				if ( cell.PossibleValues.size() == 1 ) {
					cell.Value = cell.PossibleValues.first();
					cell.PossibleValues.clear();

					throw;
				}
			}
		}
		break;
		}
		}
	}

	public Cell findEmptyCell() const {
		foreach ( int y : 1..SizeY * Repeat ) {
			foreach ( int x : 1..SizeX * Repeat ) {
				var cell const = Cells.get( cast<string>( x ) + cast<string>( y ) );

				if ( cell.Value == 0 ) {
					return cell;
				}
			}
		}

		return Cell null;
	}

	public bool isSafe(int x, int y, int value) const {
		return !isUsedInBox( x % SizeX, y % SizeY, value) && !isUsedInLine( y, value ) && !isUsedInRow( x, value );
	}

	public bool isUsedInBox(int bx, int by, int value) const {
		foreach ( int y : 1..SizeY ) {
			foreach ( int x : 1..SizeX ) {
				var cell const = Cells.get( cast<string>( bx * SizeX + x ) + cast<string>( by * SizeY + y ) );

				if ( cell.Value == value ) {
					return true;
				}
			}
		}

		return false;
	}

	public bool isUsedInLine(int y, int value) const {
		foreach ( int x : 1..SizeX * Repeat ) {
			var cell const = Cells.get( cast<string>( x ) + cast<string>( y ) );

			if ( cell.Value == value ) {
				return true;
			}
		}

		return false;
	}

	public bool isUsedInRow(int x, int value) const {
		foreach ( int y : 1..SizeY * Repeat ) {
			var cell const = Cells.get( cast<string>( x ) + cast<string>( y ) );

			if ( cell.Value == value ) {
				return true;
			}
		}

		return false;
	}

	public void set(int x, int y, int value) modify {
		var cell = Cells.get( cast<string>( x ) + cast<string>( y ) );

		cell = value;
	}

	public void solve() modify {
		var tmpBoard = copy Cells;

		while ( true ) {
			print( "size: " + Cells.size() );

			bool found = false;
			try {
				foreach ( int y : 1..SizeY * Repeat ) {
					foreach ( int x : 1..SizeX * Repeat ) {
						var xy = cast<string>( x ) + cast<string>( y );

						var cell = Cells.get( xy );
						if ( cell.Value == 0 ) {
							print( xy );

							foreach ( int value : 1..SizeX * Repeat ) {
								print( "Testing: " + value );

								if ( isSafe(x, y, value ) ) {
									print(xy + ".Value = " + value);
									cell.Value = value;
								}
							}
						}
					}
				}

				if ( !found ) {
					print( "throw: no value found!" );
					throw "no value found";
				}

				break;
			}
			catch {
				print( "catch" );
				print( toString() );

				Cells = copy tmpBoard;
			}
		}
	}

	public string toString(bool showPossibleValues = false) const {
		string result;

		foreach ( int y : 1..SizeY * Repeat ) {
			result += "[";

			foreach ( int x : 1..SizeX * Repeat ) {
				var xy = cast<string>( x ) + cast<string>( y );

				var cell const = Cells.get( xy );

				result += " " + cast<string>( cell );

				string possibleValues;

				if ( showPossibleValues ) {
					possibleValues += "(";
					foreach ( int value : cell.PossibleValues ) {
						possibleValues += value;
					}
					possibleValues = strrpad(possibleValues, SizeX * Repeat + 1, " ") + ")";
				}

				result += possibleValues + " ";
			}

			result += "]" + LINEBREAK;
		}

		return result;
	}

	public Cell operator[](int x, int y) const {
		return Cells.get( cast<string>( x ) + cast<string>( y ) );
	}

	private Map<string, Cell> Cells;
	private int Repeat;
	private int SizeX;
	private int SizeY;
}

