#!/usr/bin/env slang

// library imports
import libParam;

// project imports


public void Main( int argc, string args ) {
	var params = new ParameterHandler( argc, args );
	if ( params.empty() ) {
		print( "usage: <program> <message queue> <message>" );
		return;
	}

	if ( params.size() != 2 ) {
		print( "invalid number of parameters!!!" );
		exit( 1 );
	}

	var queueID = cast<int>( params[ 0 ].Key );
	var message = params[ 1 ].Key;

	print( "Sending \"" + message + "\" to queue \"" + queueID + "\"" );

	var handle = msgget( queueID );
	if ( !handle ) {
		print( "invalid IPC queue: " + queueID );
	}

	msgsnd( handle, "{\"message\":\"" + message + "\",\"receiver\":" + queueID + "}" );
}

