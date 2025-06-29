#!/usr/bin/env slang

import libParam;
import IPCService;


public int Main( int argc, string args )
{
    var params = new ParameterHandler( argc, args );
    if ( params.size() != 2 ) {
        print( "Usage: program <queueID> <message>" );
        return -1;
    }

    var ipc = new IPCService( cast<int>( params[ 0 ].Key ), "", false );
    ipc.send( cast<int>( params[ 0 ].Key ), params[ 1 ].Key + LINEBREAK );
}
