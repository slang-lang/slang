
// library imports

// project imports


private object Breakpoint {
	public int Line;

	public void Constructor(int line) {
		Line = line;
	}

	public bool operator==(Breakpoint other ref) const {
		return other ? Line == other.Line : false;
	}

	public bool operator==(int line) const {
		return Line == line;
	}

	public bool operator<(Breakpoint other ref) const {
		return other ? Line < other.Line : false;
	}

	public string =operator(string none) const {
		return string Line;
	}
}
