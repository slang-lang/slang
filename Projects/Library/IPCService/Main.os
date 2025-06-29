#!/usr/bin/env slang

import Application;


public void Main( int argc, string args )
{
	try {
		var logger = ILogger new StdOutLogger( "IPCService", 20 );
	
		var app = new Application( logger );
		app.Start( argc, args );
	}
	catch ( string e ) {
		print( e );
	}
	catch ( IException e ) {
		print( e.what() );
	}
}

