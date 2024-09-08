#!/usr/local/bin/slang

public void Main( int argc = 0, string args = "" ) {
    var time = time();
    var timeStr = strftime( "%Y-%m-%d %H:%M:%S", time );
    print( "time:  " + time );
	print( "strftime: " + timeStr );

	sleep( 2000 );

	var ptime = strptime( "%Y-%m-%d %H:%M:%S", timeStr );
	print( "ptime: " + ptime );
	print( "strptime: " + strftime( "%Y-%m-%d %H:%M:%S", ptime ) );
}
