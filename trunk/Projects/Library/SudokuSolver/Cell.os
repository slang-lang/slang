
// Library imports
import System.Collections.List;

// Project imports


public object Cell {
	public List<int> PossibleValues;
	public int Value;
	public int X const;
	public int Y const;

	public void Constructor(int x, int y) {
		PossibleValues = new List<int>();
		Value = 0;
		X = x;
		Y = y;
	}

	public Cell Copy() const {
		Cell result = new Cell(X, Y);
		result.PossibleValues = copy PossibleValues;
		result.Value = Value;

		return result;
	}

	public string toString() const {
		string result = Value;

		if ( ! PossibleValues.empty() ) {
			result += " (";
			foreach ( int value : PossibleValues ) {
				result += " " + cast<string>( value );
			}
			result += " )";
		}

		return result;
	}

	public Cell operator=(int value) modify {
		Value = value;

		return this;
	}

	public string =operator(string) const {
		return cast<string>( Value );
	}
}

