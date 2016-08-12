#!/usr/local/bin/oscript


public enum Day {
	Monday = 0,
	Tuesday = 1,
	Wednesday = 2,
	Thursday = 3,
	Friday = 4,
	Saturday = 5,
	Sunday = 6;
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		Day e = Day.Friday;

		print("e = " + e);

		return e == Day.Friday;
	}

	private bool TestCase2() const {
		Day e = Day.Tuesday;

		switch ( e ) {
			case Day.Monday: { return false; }
			case Day.Tuesday: { writeln("Day.Tuesday = " + e); break; }
			case Day.Wednesday: { return false; }
			default: { return false; }
		}

		return e == Day.Tuesday;
	}
}

