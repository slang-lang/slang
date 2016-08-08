#!/usr/local/bin/oscript

public enum Day {
	Monday = 0,
	Tuesday = 1,
	Wednesday = 2,
	Thursday = 3,
	Friday = 4,
	Saturday = 5,
	Sunday = 6
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		Day e = Day.Monday;

		return true;
	}
}

