#!/usr/bin/env slang

// library imports
import libParam;
import libSQLite3;
import libSQLite3.Exceptions;

// project imports


public object Client
{
	public void Constructor( string filename_ ) {
		this.filename = filename_;
	}

	public void Run() modify {
		database = new Sqlite3Database( filename );
		var result = database.exec( "SELECT name, type FROM sqlite_master" );

		print( "Error: " + database.errCode() + ", "+ database.errMsg() );
		print( "Entities(" + result.Rows.size() + "): " + cast<string>( result ) );
		print( "" );
	}

	private Sqlite3Database database;
	private string filename;
}

