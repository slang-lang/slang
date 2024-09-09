#!/usr/local/bin/slang

public enum WeekDay {
	Monday,
	Tuesday,
	Wednesday
	;
}


public void Main( int argc, string args ) {
	var day const = WeekDay.Tuesday;
	print( typeid( day ) );

	print( "day: " + cast<string>( day ) );

	int idx = 17;
	print( typeid( idx ) );
	idx = WeekDay.Wednesday;
	idx = cast<int>( day );
	print( typeid( idx ) );
}

