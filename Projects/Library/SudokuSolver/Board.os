
// Library imports
import System.Collections.Map;
import System.Collections.Range;
import System.Collections.Vector;

// Project imports
import Cell;


public object Board {
	public void Constructor(int sizeX, int sizeY, int repeat) {
		Cells = new Map<string, Cell>();
		Repeat = repeat;
		SizeX = sizeX;
		SizeY = sizeY;
		Solved = false;

		foreach ( int y : 1..SizeY * Repeat ) {
			foreach ( int x : 1..SizeX * Repeat ) {
				Cells.insert( cast<string>( x ) + "," + cast<string>( y ), new Cell(x, y) );
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
		int missingValues = 0;
		bool recalculate = true;

		while ( recalculate ) {
			missingValues = 0;
			recalculate = false;

			foreach ( int y : 1..SizeY * Repeat ) {
				foreach ( int x : 1..SizeX * Repeat ) {
					var xy = cast<string>( x ) + "," + cast<string>( y );
					var cell = Cells.get( xy );

					if ( cell.Value == 0 ) {
						cell.PossibleValues.clear();

						foreach ( int value : 1..SizeX * Repeat ) {
							if ( isSafe( x, y, value ) ) {
								cell.PossibleValues.push_back( value );
							}
						}

						missingValues++;
					}

					if ( cell.PossibleValues.size() == 1 ) {
						cell.Value = cell.PossibleValues.first();
						cell.PossibleValues.clear();

						missingValues--;
						recalculate = true;
					}
				}
			}
		}

		Solved = missingValues == 0;
	}

	public Cell findEmptyCell() const {
		foreach ( int y : 1..SizeY * Repeat ) {
			foreach ( int x : 1..SizeX * Repeat ) {
				var xy = cast<string>( x ) + "," + cast<string>( y );
				var cell const = Cells.get( xy );

				if ( cell.Value == 0 ) {
					return cell;
				}
			}
		}

		return Cell null;
	}

	public Cell getCell(int x, int y) const {
		return Cells.get( cast<string>( x ) + "," + cast<string>( y ) );
	}

	public bool isSafe(int x, int y, int value) const {
		return  !isUsedInBox( (x - 1) / SizeX, (y - 1) / SizeY, value ) &&
			!isUsedInLine( y, value ) &&
			!isUsedInRow( x, value );
	}

	public bool isUsedInBox(int bx, int by, int value) const {
		foreach ( int y : 1..Repeat ) {
			foreach ( int x : 1..Repeat ) {
				var xy = cast<string>( bx * SizeX + x ) + "," + cast<string>( by * SizeY + y );
				var cell const = Cells.get( xy );

				if ( cell.Value == value ) {
					return true;
				}
			}
		}

		return false;
	}

	public bool isUsedInLine(int y, int value) const {
		foreach ( int x : 1..SizeX * Repeat ) {
			var cell const = Cells.get( cast<string>( x ) + "," + cast<string>( y ) );

			if ( cell.Value == value ) {
				return true;
			}
		}

		return false;
	}

	public bool isUsedInRow(int x, int value) const {
		foreach ( int y : 1..SizeY * Repeat ) {
			var cell const = Cells.get( cast<string>( x ) + "," + cast<string>( y ) );

			if ( cell.Value == value ) {
				return true;
			}
		}

		return false;
	}

	public void set(int x, int y, int value, bool validate = false) modify {
		if ( validate ) {
			assert( isSafe(x, y, value ) );
		}

		var cell = Cells.get( cast<string>( x ) + "," + cast<string>( y ) );
		cell = value;

		Solved = false;
	}

	public void solve() modify {
		if ( Solved ) {
			// board is already solved;
			return;
		}

		var cells = new Vector<Cell>();

		foreach ( int y : 1..SizeY * Repeat ) {
			foreach ( int x : 1..SizeX * Repeat ) {
				var xy = cast<string>( x ) + "," + cast<string>( y );
				var cell = Cells.get( xy );

				if ( cell.Value == 0 ) {
					cells.push_back( cell );
				}
			}
		}

		Solved = cells.empty();
		if ( !Solved ) {
			Solved = solve( cells, 0 );
		}

		print( "Solved: " + Solved );
	}

	private bool solve(Vector<Cell> cells, int index) const {
		//print( "index: " + index );

		foreach ( int idx : index..(cells.size() - 1) ) {
			var cell = cells.at(idx);
			cell.Value = 0;
		}

		foreach ( int idx : index..(cells.size() - 1) ) {
			//print( "idx: " + idx );

			var cell = cells.at(idx);
			cell.Value = 0;

			foreach ( int value : cell.PossibleValues ) {
				if ( isSafe(cell.X, cell.Y, value) ) {
					//print( cast<string>( cell.X ) + "," + cast<string>( cell.Y ) + ": " + value );
					cell.Value = value;

					print( toString() );

					if ( solve(cells, index + 1) ) {
						return true;
					}
				}
			}
		}

		return false;
	}

	public string toString(bool showPossibleValues = false) const {
		string result;

		foreach ( int y : 1..SizeY * Repeat ) {
			result += "[";

			foreach ( int x : 1..SizeX * Repeat ) {
				var xy = cast<string>( x ) + "," + cast<string>( y );

				var cell const = Cells.get( xy );

				//result += ((x - 1 == Repeat) ? "| " : " ") + cast<string>( cell );
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

/*
			if ( y == Repeat ) {
				result += "_______________" + LINEBREAK + LINEBREAK;
			}
*/
		}

		return result;
	}

	private Map<string, Cell> Cells;
	private int Repeat;
	private int SizeX;
	private int SizeY;
	private bool Solved;
}

