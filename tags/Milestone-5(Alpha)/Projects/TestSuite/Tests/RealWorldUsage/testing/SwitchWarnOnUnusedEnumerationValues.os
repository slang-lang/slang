#!/usr/local/bin/oscript

private enum Days {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday;
}

public void Main(int argc, string args) {
	Days day = Days.Monday;

	switch ( day ) {
		case Days.Monday: { break; }
		case Days.Tuesday: { return; }
	}

	print("Damn you mondays!");
}

