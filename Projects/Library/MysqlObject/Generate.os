#!/usr/local/bin/slang

// Library imports
import libParam;

// Project imports
import CodeGenerator;
import ConfigLoader;
import Consts;


public void Main( int argc, string args ) modify throws {
	try {
		var cfg = processParameters( new ParameterHandler( argc, args ) );

		var config = new ConfigLoader( cfg + "/generate.json" );
		if ( System.IO.File.Exists( cfg + "/generate.json" ) ) {
			config.load();
		}

		if ( !Config.Database ) {
			print( "database missing!" );
			exit( -1 );
		}

		var generator = new CodeGenerator();
		generator.process();

		config.store();
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

private string processParameters( ParameterHandler params ) modify {
	if ( params.empty() ) {
		printUsage();
		exit( 0 );
	}

	if ( params.contains( "version" ) ) {
		printVersion();
		exit( 0 );
	}

	if ( params.contains( "database" ) ) {
		Config.Database = params[ "database" ].Value;
		params.remove( "database" );
	}
	if ( params.contains( "host" ) ) {
		Config.Host = params[ "host" ].Value;
		params.remove( "host" );
	}
	if ( params.contains( "output" ) ) {
		Config.Output = params[ "output" ].Value;
		params.remove( "output" );
	}
	if ( params.contains( "password" ) ) {
		Config.Password = params[ "password" ].Value;
		params.remove( "password" );
	}
	if ( params.contains( "port" ) ) {
		Config.Port = cast<int>( params[ "port" ].Value );
		params.remove( "port" );
	}
	if ( params.contains( "user" ) ) {
		Config.User = params[ "user" ].Value;
		params.remove( "user" );
	}

	if ( !Config.Output ) {
		Config.Output = Config.Database;
	}

	return params.empty() ? Config.Output : params[ 0 ].Key;
}

private void printUsage() {
	print( "Usage: program [options]" );
	print( "" );
	print( "	--database	sets the database schema to connect to" );
	print( "	--host		sets the host to connect to" );
	print( "	--output	sets the output folder for the generated files (default: current directory)" );
	print( "	--password	sets the password used to connect to the database" );
	print( "	--port		sets the port used to connected to the database" );
	print( "	--user		sets the user used to connect to the database" );
	print( "	--version	print program version" );
	print( "" );
}

private void printVersion() {
	print( APP_NAME + " " + APP_VERSION + " " + APP_COPYRIGHT );
	print( "" );
}

