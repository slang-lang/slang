#!/usr/local/bin/slang

// library imports
import libCSVReader;
import libParam;

// project imports
import App;
import Consts;


public int Main( int argc, string args )
{
    var params = new ParameterHandler( argc, args );

    if( params.contains( "help" ) ) {
        printHelp();
        return 0;
    }
    else if ( params.contains( "version" ) ) {
        printVersion();
        return 0;
    }

    ( new App( params ) ).Run();

    return 0;
}

private void printHelp()
{
    print( "Usage: <program> [filename(s)]" );
}

private void printVersion()
{
    print( APPNAME + " v" + VERSION );
}

