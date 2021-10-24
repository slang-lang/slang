#!/usr/local/bin/slang

// library imports
import libParam;

// project imports


public void Main( int argc, string args ) {
	var params = new ParameterHandler( argc, args );
	if (  params.empty(  )  ) {
		print( "usage: <program> <message queue> <message>" );
		return;
	}

	if (  params.size(  ) != 2  ) {
		print( "invalid number of parameters!!!" );
		exit( 1 );
	}

	int queueID = cast<int>(  params[ 0 ].Key  );
	string message = params[ 1 ].Key;

	print( "Sending \"" + message + "\" to queue \"" + queueID + "\"" );

	int handle = msgget( queueID );
	if (  !handle  ) {
		print( "invalid IPC queue: " + queueID );
	}

	msgsnd( handle, "{\"message\":\"" + message + "\",\"receiver\":" + queueID + "}" );
}

