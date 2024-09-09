#!/usr/local/bin/slang

public void Main( int argc = 0, string args = "" ) {
    var time = time();
    var timeStr = strftime( "%Y-%m-%d %H:%M:%S", time );

	print( "Time: " + timeStr );
}
