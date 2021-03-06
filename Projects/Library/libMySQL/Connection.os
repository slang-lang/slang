
// Library imports

// Project imports
import Exceptions;
import Result;
import Settings;
import Statement;

public namespace Mysql { }

public object MysqlConnection {
// Public

	public void Constructor() {
		initialize();
	}

	public void Constructor( int handle ) {
		initialize();

		mHandle = handle;
	}

	public void Constructor( string hostname, int port, string user, string password, string database = "" ) {
		initialize();

		open( hostname, port, user, password, database );
	}

	public void Destructor() {
		close();
	}

	public int affectedRows() const throws {
		return mysql_affected_rows( mHandle );
	}

	private void cleanup() modify {
		mDatabase = "";
		mHandle = 0;
		mHostname = "";
		mPassword = "";
		mPort = 0;
		mUsername = "";
	}

	public void close() modify {
		if ( mHandle ) {
			mysql_close( mHandle );

			cleanup();
		}
	}

	public MysqlStatement createStatement( string queryStr = "" ) const {
		return new MysqlStatement( mHandle, queryStr );
	}

	public string error() const throws {
		return mysql_error( mHandle );
	}

	public string info() const throws {
		return mysql_info( mHandle );
	}

	public bool isOpen() const {
		return mHandle != 0;
	}

	public int numRows() const throws {
		return mysql_num_rows( mHandle );
	}

	public bool open( string hostname, int port, string user, string password, string database = "" ) modify throws {
		if ( mHandle != 0 ) {
			// we already have a connection handle
			throw new MysqlException( "mysql handle still points to an open connection!" );
		}

		// request a mysql handle
		mHandle = mysql_init();
		// connect to mysql database and update our handle
		mHandle = mysql_real_connect( mHandle, hostname, port, user, password, database );

		mDatabase = database;
		mHostname = hostname;
		mPassword = password;
		mPort = port;
		mUsername = user;

		return isOpen();
	}

	public bool ping() const {
		return mysql_ping( mHandle ) == 0;
	}

	public MysqlResult query( string queryStr ) modify throws {
		if ( mSettings.getAutoEscaping() ) {
			// auto escaping for strings is active
			queryStr = mysql_real_escape_string( mHandle, queryStr );
		}

		int error = mysql_query( mHandle, queryStr );
		if ( error ) {
			// error while query execution
			throw new MysqlException( mysql_error( mHandle ) );
		}

		return new MysqlResult( mysql_store_result( mHandle ) );
	}

	public bool selectDB( string database ) modify {
		int result = mysql_select_db( mHandle, database );
		if ( result == 0 ) {
			// success! so we can update our database
			mDatabase = database;
		}

		return result == 0;
	}

	public MysqlSettings settings() const {
		return mSettings;
	}

	public string stat() const {
		return mysql_stat( mHandle );
	}

// Private

	private void initialize() modify {
		assert( !mSettings );	// prevent multiple initializations

		mSettings = new MysqlSettings();
	}

	private string mDatabase;
	private int mHandle;
	private string mHostname;
	private string mPassword;
	private int mPort;
	private MysqlSettings mSettings;
	private string mUsername;
}

