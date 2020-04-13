
// Library imports
import System.String;

// Project imports
import Connection;
import Exceptions;
import Result;
import Settings;

public namespace Mysql { }

public object MysqlStatement {
// Public

	// Standard constructor with MysqlConnection
	public void Constructor( MysqlConnection connection, string queryStr = "" ) {
		mConnection = connection;
		mExecutedQuery = new String();
		mPreparedQuery = new String();

		prepare( queryStr );
	}

	// Old-school constructor with MySQL handle
	public void Constructor( int handle, string queryStr = "" ) {
		Constructor( new MysqlConnection( handle ), queryStr );
	}

	public void Destructor() {
		// nothing to do here
	}

	public MysqlStatement bind( string field, bool value ) modify {
		// replace all occurances of field with value
		mExecutedQuery.ReplaceAll( field, cast<string>( value ) );

		return this;
	}

	public MysqlStatement bind( string field, double value ) modify {
		// replace field with value
		mExecutedQuery.ReplaceAll( field, cast<string>( value ) );

		return this;
	}

	public MysqlStatement bind(string field, float value) modify {
		// replace field with value
		mExecutedQuery.ReplaceAll(field, cast<string>( value) );

		return this;
	}

	public MysqlStatement bind( string field, int value ) modify {
		// replace field with value
		mExecutedQuery.ReplaceAll( field, cast<string>( value ) );

		return this;
	}

	public MysqlStatement bind( string field, string value ) modify {
		// replace field with value
		mExecutedQuery.ReplaceAll( field, value );

		return this;
	}

	public MysqlResult execute( string queryStr = "" ) modify throws {
		if ( queryStr ) {
			prepare( queryStr );
		}

		queryStr = cast<string>( mExecutedQuery );

		int error = mysql_query( mConnection.mHandle, queryStr );
		if ( error ) { 
			// error while query execution
			throw new MysqlException( mysql_error( mConnection.mHandle ) );
		}

		return new MysqlResult( mysql_store_result( mConnection.mHandle ) );
	}

	public string getQuery() const {
		return cast<string>( mExecutedQuery );
	}

	public void prepare( string query ) modify {
		mExecutedQuery = query;
		mPreparedQuery = query;
	}

// Private

	private MysqlConnection mConnection;
	private String mExecutedQuery;
	private String mPreparedQuery;
}

