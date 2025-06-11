#!/usr/bin/env slang

import libParam;
import MsgQueue;


public int Main( int argc, string args )
{
    var params = new ParameterHandler( argc, args );
    if ( params.size() != 1 ) {
        print( "Usage: program <queueID>" );
        return -1;
    }

    var queue = new MsgQueue( cast<int>( params[ 0 ].Key ), true );
    print( "Received '" + queue.Receive( true ) + "'" );
}
