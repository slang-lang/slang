#!/usr/local/bin/slang

import Nodes;
import TestTree;
import TestTree.FridgeTest;

public void Main( int argc, string args ) {
    print( "Behaviour Tree Test" );

    var root = new Sequence( "root" );
    root.pushChild( Node new PrintAction( "print" ) );
    root.pushChild( Node new InputAction() );

    var status = root.tick();
    print( "Status: " + string status );
}
