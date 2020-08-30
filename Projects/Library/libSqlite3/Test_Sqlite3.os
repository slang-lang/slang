#!/usr/local/bin/slang

// library imports
//import libParam.ParameterHandler;

// project imports
import All;


public void Main( int argc, string args ) {
	//var params = new ParameterHandler( argc, args );

	var db = new Sqlite3Database( "test.db" );
	var result = db.exec( "SELECT name, type FROM sqlite_master" );

	try {
		print( "ErrorCode: " + db.errCode() );
		print( "ErrroMessage: " + db.errMsg() );
		print( "Results(" + result.Rows.size() + ") = " + cast<string>( result ) );

		int maxColLength;

		int rowIdx;
		foreach ( Sqlite3Row row : result ) {
			//print( "Row(" + rowIdx + "): " );

			string line;

			int entryIdx;
			foreach ( Sqlite3Entry e : row ) {
				if ( line ) {
					line += "|";
				}
				line += e.Value;

				maxColLength = (maxColLength < strlen(e.Value)) ? strlen(e.Value) : maxColLength;

				//print( "Entry(" + entryIdx + "): " + cast<string>( e ) );
				entryIdx++;
			}

			print( "|" + line + "|" );

			rowIdx++;
		}
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}
	catch {
		print( "Unknown exception!" );
	}
}

