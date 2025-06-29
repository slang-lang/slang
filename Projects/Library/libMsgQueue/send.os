#!/usr/bin/env slang

import libParam;
import MsgQueue;


public int Main( int argc, string args )
{
    var params = new ParameterHandler( argc, args );
    if ( params.size() != 2 ) {
        print( "Usage: program <queueID> <message>" );
        return -1;
    }

    var queue = new MsgQueue( cast<int>( params[ 0 ].Key ) );
    queue.Send( params[ 1 ].Key + LINEBREAK );
}
