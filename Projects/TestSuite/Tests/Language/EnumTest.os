#!/usr/local/bin/oscript

public enum Day {
	Monday = 0,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday;
}

/*
public object Days {
	public enum E {
		Monday = 0,
		Tuesday = 1;
	}
}
*/

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	Day e = Day.Friday;
	print("e = " + e);

	e = Day.Wednesday;
	print("e = " + e);

	e = 17;
	print("e = " + e);

	e = Day.Friday;
	return e == Day.Friday;
}

private bool TestCase2() const {
	Day e = Day.Tuesday;

	switch ( e ) {
		case Day.Monday: { return false; }
		case Day.Tuesday: { print("e = " + e); break; }
		case Day.Wednesday: { return false; }
		default: { return false; }
	}

	return e == Day.Tuesday;
}

