#!/usr/local/bin/slang

public void Main( int , string ) {
    print( "Test: setlocale()" );

    setlocale(LC_ALL, "en_US.UTF-8");
    setlocale(LC_NUMERIC, "de_DE.utf8");
    setlocale(LC_TIME, "de_DE.utf8");

    print( "done." );
}
