#!/usr/bin/env slang

import libs.CoreUtils.ShellCommand;


public void Main( int argc, string args )
{
	var cmd = new ShellCommand( "uname" );

	print( cmd.Run( "-a" ) );

	// print( cast<string>( cmd[ 0 ] ) );
}

