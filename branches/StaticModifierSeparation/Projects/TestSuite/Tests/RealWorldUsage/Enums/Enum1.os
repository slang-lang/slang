#!/usr/local/bin/oscript

public enum Day {
	SUNDAY = 0,
	MONDAY = 1,
	TUESDAY = 2,
	WEDNESDAY = 3,
	THURSDAY = 4,
	FRIDAY = 5,
	SATURDAY = 6;
}

public object EnumTest {
	private Day mDay;
    
	public void Constructor(int day) {
		mDay = day;
	}
    
	public void tellItLikeItIs() {
		switch ( mDay ) {
			case Day.MONDAY: {
				writeln("Mondays are bad.");
				break;
			}
			case Day.FRIDAY: {
				writeln("Fridays are better.");
				break;
			}
			case Day.SATURDAY: {
				writeln("Weekends are best.");
				break;
			}
			case Day.SUNDAY: {
				writeln("Weekends are best.");
				break;
			}
			default: {
				writeln("Midweek days are so-so.");
				break;
			}
		}
	}
}

public void Main(int argc, string args) {
	Day monday = Day.MONDAY;
	print("typeid(monday) = " + typeid(monday));
	print("typeid(Day.MONDAY) = " + typeid(Day.MONDAY));
	print("");

	write("Monday: ");
	EnumTest firstDay = new EnumTest(monday);
	firstDay.tellItLikeItIs();

	write("Tuesday: ");
	EnumTest secondDay = new EnumTest(Day.TUESDAY);
	secondDay.tellItLikeItIs();

	write("Wednesday: ");
	EnumTest thirdDay = new EnumTest(Day.WEDNESDAY);
	thirdDay.tellItLikeItIs();

	write("Thursday: ");
	EnumTest forthDay = new EnumTest(Day.THURSDAY);
	forthDay.tellItLikeItIs();

	write("Firday: ");
	EnumTest fifthDay = new EnumTest(Day.FRIDAY);
	fifthDay.tellItLikeItIs();

	write("Saturday: ");
	EnumTest sixthDay = new EnumTest(Day.SATURDAY);
	sixthDay.tellItLikeItIs();

	write("Sunday: ");
	EnumTest seventhDay = new EnumTest(Day.SUNDAY);
	seventhDay.tellItLikeItIs();
}

