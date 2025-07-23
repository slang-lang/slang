#!/usr/bin/env slang

// library imports
import libParam;
import libSQLite3;
import libSQLite3.Exceptions;

// project imports


public void Main( int argc, string args )
{
	if ( argc < 2 ) {
		print( "usage: program [arg1 [arg2 [...] ] ]" );
		print( "" );
		return;
	}

	try {
		var params = new ParameterHandler( argc, args );

		foreach ( Parameter filename : params ) {
			if ( params.size() > 1 ) {
				print( filename.Key + ":" );
			}

            var db = new Sqlite3Database( filename.Key );
            var result = db.exec( "SELECT name, type FROM sqlite_master" );

            print( "Error: " + db.errCode() + ", "+ db.errMsg() );
            print( "Entities(" + result.Rows.size() + "): " + cast<string>( result ) );
            print( "" );
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
}
