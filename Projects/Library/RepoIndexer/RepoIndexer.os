#!/usr/bin/env slang

// Library imports
import libParam;

// Project imports
import Consts;
import Indexer;


public int Main( int argc, string args ) modify {
	try {
		var params = new ParameterHandler( argc, args, true );

		var main = new Indexer( params.empty() ? PATH : params[ 0 ].Key );
		main.buildIndex();
		main.storeDatabase();
		main.storeIndexFile();

		return 0;
	}
	catch (  string e  ) {
		print( "Exception: " + e );
	}
	catch (  IException e  ) {
		print( "Exception: " + e.what() );
	}
	catch {
		print( "Unknown exception caught!" );
	}

	return -1;
}

