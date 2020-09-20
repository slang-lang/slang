#!/usr/local/bin/slang

import StdOutLogger;


public void Main( int argc, string args ) {
	var logger = new StdOutLogger( "Main" );

	logger.info( "Info message" );
	logger.warning( "This is a warning" );
}

