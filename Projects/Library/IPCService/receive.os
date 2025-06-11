#!/usr/bin/env slang

import libParam;
import IPCService;


public int Main( int argc, string args )
{
    var params = new ParameterHandler( argc, args );
    if ( params.size() != 1 ) {
        print( "Usage: program <queueID>" );
        return -1;
    }

    var ipc = new IPCService( cast<int>( params[ 0 ].Key ), "", true );
    print( "Received '" + cast<string>( ipc.receive( true ) ) + "'" );
}
