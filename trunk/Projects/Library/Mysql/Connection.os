
//import System.GDI.IConnection;
import Debug;
import Exceptions;
import Query;
import Result;
import Settings;

public namespace Mysql
{
	public object Connection //implements System.GDI.IConnection
	{
		private string mDatabase;
		private int mHandle;
		private string mHostName;
		private string mPassword;
		private int mPort;
		private Settings mSettings;
		private string mUserName;

		public void Connection() {
			initialize();

			cleanup();
		}

		public void Connection(string hostname, int port, string user, string password, string database = "") {
			initialize();

			open(hostname, port, user, password, database);
		}

		public void ~Connection() {
			if ( mHandle != 0 ) {
				close();
			}
		}

		public int affectedRows() const {
			return mysql_affected_rows();
		}

		private void cleanup() modify {
			mDatabase = "";
			mHandle = 0;
			mHostName = "";
			mPassword = "";
			mPort = 0;
			mUserName = "";
		}

		public void close() modify {
			if ( mHandle == 0 ) {
				return false;
			}

			mysql_close(mHandle);

			cleanup();
		}

		public Query createQuery(string queryStr = "") const {
			return new Query(this, queryStr);
		}

		public string error() const {
			return mysql_error(mHandle);
		}

		public int handle() const {
			return mHandle;
		}

		public string info() const {
			return mysql_info(mHandle);
		}

		private void initialize() modify {
			assert(!mSettings);

			mSettings = new Settings();
		}

		public bool isOpen() const {
			return (mHandle != 0);
		}

		public int numRows() const {
			return mysql_num_rows(mHandle);
		}

		public bool open(string hostname, int port, string user, string password, string database) modify {
			if ( mHandle != 0 ) {
				// we already have a connection handle
				throw new Exception("mysql handle still points to an open connection!");
			}

			// request a mysql handle
			mHandle = mysql_init();
			// connect to mysql database and update our handle
			mHandle = mysql_real_connect(mHandle, hostname, port, user, password, database);

			mDatabase = database;
			mHostName = hostname;
			mPassword = password;
			mPort = port;
			mUserName = user;

			return (mHandle != 0);
		}

		public Result query(string queryStr) modify {
			Result result;	// null object

			if ( MysqlDebugMode ) {
				writeln("Mysql debug mode is enabled.");
			}

			if ( mSettings.getAutoEscaping() ) {
				// auto escaping for strings is active
				queryStr = mysql_real_escape_string(mHandle, queryStr);
			}

			int error = mysql_query(mHandle, queryStr);
			if ( error != 0 ) {
				// error while query execution
				return result;	// return uninitialized result object
			}

			int result_handle = mysql_store_result(mHandle);
			return new Result(result_handle);
		}

		public int selectDB(string database) modify {
			return mysql_select_db(mHandle, database);
		}

		public Settings settings() const {
			return mSettings;
		}

		public string stat() const {
			return mysql_stat(mHandle);
		}
	}
}

