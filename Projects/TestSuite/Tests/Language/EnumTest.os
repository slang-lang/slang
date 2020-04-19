#!/usr/local/bin/slang

public enum Day {
	Monday = 0,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday;
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() {
	print("TestCase 1");

	Day e = Day.Friday;
	print("e = " + string e);

	e = Day.Wednesday;
	print("e = " + string e);

	e = Day.Friday;
	return e == Day.Friday;
}

private bool TestCase2() {
	print("TestCase 2");

	Day e = Day.Tuesday;

	switch ( e ) {
		case Day.Monday: { return false; }
		case Day.Tuesday: { print("e = " + string e); break; }
		case Day.Wednesday: { return false; }
		default: { return false; }
	}

	return e == Day.Tuesday;
}

private bool TestCase3() {
	print("TestCase 3: operator < and <=");

	// operator<
	assert( Day.Monday < Day.Tuesday );
	assert( Day.Wednesday < Day.Sunday );
	assert( !(Day.Saturday < Day.Thursday) );

	// operator<=
	assert( Day.Monday <= Day.Monday );
	assert( Day.Saturday <= Day.Sunday );

	return true;
}

private bool TestCase4() {
	print("TestCase 4: operator > and >=");

	//operator>
	assert( Day.Tuesday > Day.Monday );
	assert( Day.Thursday > Day.Tuesday );
	assert( !(Day.Saturday > Day.Sunday) );

	// operator>=
	assert( Day.Tuesday >= Day.Tuesday );
	assert( Day.Sunday >= Day.Friday );

	return true;
}

