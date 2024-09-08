#!/usr/local/bin/slang

public void Main( int , string ) {
    print( "STDIN: " + STDIN );
    print( "STDOUT: " + STDOUT );
    print( "STDERR: " + STDERR );
    print( "fgets: " + fgets( STDIN, 3 ) );
    print( "done." );
}