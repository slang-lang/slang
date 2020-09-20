#!/usr/local/bin/slang

import FileLogger;


public void Main( int argc, string args ) {
	var logger = new AppendingFileLogger( "test.log", "Main" );

	logger.info( "Info message" );
	logger.warning( "This is a warning" );
}

