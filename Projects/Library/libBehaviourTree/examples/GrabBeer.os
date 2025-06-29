#!/usr/bin/env slang

import Nodes;
import TestTree;
import TestTree.FridgeTest;

public void Main( int argc, string args ) {
    print( "Behaviour Tree Test" );

    var root = new Sequence( "root" );

    try {
/*
        // Force success
        var forceSuccess = new ForceSuccessDecorator();
        forceSuccess.pushChild( Node new GrabBeer() );

        root.pushChild( Node new OpenFridge() );
        root.pushChild( Node forceSuccess );
        root.pushChild( Node new CloseFridge() );
*/

        // Fallback
        var forceFailure = new ForceFailureDecorator();
        forceFailure.pushChild( Node new CloseFridge() );

        var fallback = new Fallback( "GrabBeerFallback" );
        fallback.pushChild( Node new GrabBeer( 1 ) );
        fallback.pushChild( Node forceFailure );

        root.pushChild( Node new OpenFridge() );
        root.pushChild( Node fallback );
        root.pushChild( Node new CloseFridge() );

    }
    catch ( string e ) {
        print( "Exception: " + e );
    }
    catch ( IException e ) {
        print( "Exception: " + e.what() );
    }

    //root.print();

    var status = root.tick();
    print( "Status: " + string status );
}
