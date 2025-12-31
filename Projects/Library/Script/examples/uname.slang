#!/usr/bin/env slang

import libs.CoreUtils.ShellCommand;


public void Main( int argc, string args )
{
	var cmd = new ShellCommand( "uname" );

	write( cmd.Run( "-a" ) );
}

