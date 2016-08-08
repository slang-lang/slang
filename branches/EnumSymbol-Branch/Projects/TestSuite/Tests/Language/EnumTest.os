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

/*
public enum DayTime {
	Morning = 0;
	Day = 1;
	Evening = 2;
	Night = 3;
}
*/

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		//assert( TestCase2() );
	}

	private bool TestCase1() const {
		Day e = Day.Monday;

		return e == Day.Monday;
	}

	private bool TestCase2() const {
		DayTime e = DayTime.Evening;

		return e == DayTime.Evening;
	}
}

