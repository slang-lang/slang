#!/usr/local/bin/slang

public void Main( int , string ) {
    print( "Test: assert()" );

    assert( true );
    assert( true, "true" );
    assert( false );
    assert( false, "false" );

    print( "done." );
}
