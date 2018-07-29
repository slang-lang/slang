
// Library imports

// Project imports
import Exceptions;
import Query;
import Result;
import Settings;

public namespace Mysql { }

public object MysqlConnection {
// Public interface

	public void Constructor() {
		initialize();

		cleanup();
	}

	public void Constructor(string hostname, int port, string user, string password, string database = "") {
		initialize();

		open(hostname, port, user, password, database);
	}

	public void Destructor() {
		if ( mHandle != 0 ) {
			close();
		}
	}

	public int affectedRows() const throws {
		return mysql_affected_rows(mHandle);
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
			mysql_close(mHandle);

			cleanup();
		}
	}

	public MysqlQuery createQuery(string queryStr = "") const {
		return new MysqlQuery(this, queryStr);
	}

	public string error() const throws {
		return mysql_error(mHandle);
	}

	public int handle() const {
		return mHandle;
	}

	public string info() const throws {
		return mysql_info(mHandle);
	}

	private void initialize() modify {
		assert(!mSettings);	// prevent multiple initializations

		mSettings = new MysqlSettings();
	}

	public bool isOpen() const {
		return (mHandle != 0);
	}

	public int numRows() const throws {
		return mysql_num_rows(mHandle);
	}

	public bool open(string hostname, int port, string user, string password, string database = "") modify throws {
		if ( mHandle != 0 ) {
			// we already have a connection handle
			throw new Exception("mysql handle still points to an open connection!");
		}

		// request a mysql handle
		mHandle = mysql_init();
		// connect to mysql database and update our handle
		mHandle = mysql_real_connect(mHandle, hostname, port, user, password, database);

		mDatabase = database;
		mHostname = hostname;
		mPassword = password;
		mPort = port;
		mUsername = user;

		return (mHandle != 0);
	}

	public bool ping() const {
		return mysql_ping(mHandle) == 0;
	}

	public MysqlResult query(string queryStr) modify throws {
		if ( mSettings.getAutoEscaping() ) {
			// auto escaping for strings is active
			queryStr = mysql_real_escape_string(mHandle, queryStr);
		}

		int error = mysql_query(mHandle, queryStr);
		if ( error ) {
			// error while query execution
			throw mysql_error(mHandle);
		}

		return new MysqlResult(mysql_store_result(mHandle));
	}

	public int selectDB(string database) modify {
		int result = int mysql_select_db(mHandle, database);

		if ( !result ) {
			// success! so we can update our database
			mDatabase = database;
		}

		return result;
	}

	public MysqlSettings settings() const {
		return mSettings;
	}

	public string stat() const {
		return mysql_stat(mHandle);
	}

// Private

	private string mDatabase;
	private int mHandle;
	private string mHostname;
	private string mPassword;
	private int mPort;
	private MysqlSettings mSettings;
	private string mUsername;
}

