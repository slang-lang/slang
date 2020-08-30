#!/usr/local/bin/slang

// Library imports
import libParam.ParameterHandler;
import System.IO.File;

// Project imports
import CodeGenerator;


public void Main( int argc, string args ) modify throws {
	var params = new ParameterHandler( argc, args );

	if ( params.empty() ) {
		printUsage();
		exit( 0 );
	}

	if ( !params.contains( "database" ) ) {
		print( "database missing!" );
		exit( -1 );
	}

	if ( params.contains( "database" ) ) {
		Database = params.getParameter( "database" ).Value;
	}
	if ( params.contains( "host" ) ) {
		Host = params.getParameter( "host" ).Value;
	}
	if ( params.contains( "output" ) ) {
		Output = params.getParameter( "output" ).Value;
	}
	if ( params.contains( "password" ) ) {
		Password = params.getParameter( "password" ).Value;
	}
	if ( params.contains( "port" ) ) {
		Port = cast<int>( params.getParameter( "port" ).Value );
	}
	if ( params.contains( "user" ) ) {
		User = params.getParameter( "user" ).Value;
	}

	if ( !Output ) {
		Output = Database;
	}

	try {
		var generator = new CodeGenerator();
		generator.process();
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
	catch {
		print( "Exception: caught unknown exception" );
	}
}


void printUsage() {
	print( "Usage: program [options]" );
	print( "" );
	print( "	--database	Database" );
	print( "	--host		Host" );
	print( "	--output	Output folder" );
	print( "	--password	Password" );
	print( "	--port		Port" );
	print( "	--user		User" );
	print( "" );
}

