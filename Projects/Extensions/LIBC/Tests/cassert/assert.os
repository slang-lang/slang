#!/usr/bin/env slang

public void Main( int , string ) {
    print( "Test: assert()" );

    assert( true );
    assert( true, "Your assertion did not fail." );
    //try { assert( false ); }
    try { assert( false, "Your assertion failed." ); }

    print( "done." );
}
