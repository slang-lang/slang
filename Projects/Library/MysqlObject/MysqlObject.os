#!/usr/local/bin/slang

// Library imports
import libParam.ParameterHandler;

// Project imports
import CodeGenerator;
import Consts;


public void Main( int argc, string args ) modify throws {
	try {
		processParameters( new ParameterHandler( argc, args ) );

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

private void processParameters( ParameterHandler params const ) {
	if ( params.empty() ) {
		printUsage();
		exit( 0 );
	}

	if ( params.contains( "version" ) ) {
		printVersion();
		exit( 0 );
	}

	if ( !params.contains( "database" ) ) {
		print( "database missing!" );
		exit( -1 );
	}

	if ( params.contains( "database" ) ) {
		Database = params[ "database" ].Value;
	}
	if ( params.contains( "host" ) ) {
		Host = params[ "host" ].Value;
	}
	if ( params.contains( "output" ) ) {
		Output = params[ "output" ].Value;
	}
	if ( params.contains( "password" ) ) {
		Password = params[ "password" ].Value;
	}
	if ( params.contains( "port" ) ) {
		Port = cast<int>( params[ "port" ].Value );
	}
	if ( params.contains( "user" ) ) {
		User = params[ "user" ].Value;
	}

	if ( !Output ) {
		Output = Database;
	}
}

private void printUsage() {
	print( "Usage: program [options]" );
	print( "" );
	print( "	--database	sets the database schema to connect to" );
	print( "	--host		sets the host to connect to" );
	print( "	--output	sets the output folder for the generated files (default: current directory)" );
	print( "	--password	sets the password used to connected to the database" );
	print( "	--port		sets the port used to connected to the database" );
	print( "	--user		sets the user to connect to the database" );
	print( "	--version	print program version" );
	print( "" );
}

private void printVersion() {
	print( APP_NAME + " v" + APP_VERSION );
	print( "" );
}
