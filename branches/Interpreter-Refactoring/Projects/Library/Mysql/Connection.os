
//import System.GDI.IConnection;
import Debug;
import Exceptions;
import Query;
import Result;
import Settings;

public namespace Mysql {
	public object Connection /*implements System.GDI.IConnection*/ {
		private string mDatabase;
		private int mHandle;
		private string mHostname;
		private string mPassword;
		private int mPort;
		private Mysql.Settings mSettings;
		private string mUsername;

		public void Constructor() modify {
			initialize();

			cleanup();
		}

		public void Constructor(string hostname, int port, string user, string password, string database = "") modify {
			initialize();

			open(hostname, port, user, password, database);
		}

		public void Destructor() modify {
			print("~Connection()");
			if ( mHandle != 0 ) {
				close();
			}
		}

		public string ToString() const {
			return "Hostname=" + mHostname + ", Port=" + mPort + ", Username=" + mUsername + ", Database=" + mDatabase;
		}

		public int affectedRows() const {
			return mysql_affected_rows();
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

		public Mysql.Query createQuery(string queryStr = "") const {
			return new Mysql.Query(Mysql.Connection this, queryStr);
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
			assert(!mSettings);	// prevent multiple initializations

			mSettings = new Mysql.Settings();
		}

		public bool isOpen() const {
			return (mHandle != 0);
		}

		public int numRows() const {
			return mysql_num_rows(mHandle);
		}

		public bool open(string hostname, int port, string user, string password, string database = "") modify {
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
			int error = mysql_ping(mHandle);
			return error == 0;
		}

		public Mysql.Result query(string queryStr) modify {
			if ( Mysql.MysqlDebugMode ) { writeln("Mysql debug mode is enabled."); }

			if ( mSettings.getAutoEscaping() ) {
				// auto escaping for strings is active
				queryStr = mysql_real_escape_string(mHandle, queryStr);
			}

			int error = mysql_query(mHandle, queryStr);
			if ( error ) {
				// error while query execution
				print(mysql_error(mHandle));
				return null;
			}

			int handle = mysql_store_result(mHandle);
			return new Mysql.Result(handle);
		}

		public int selectDB(string database) modify {
			int result = mysql_select_db(mHandle, database);

			if ( !result ) {
				// success! so we can update our database
				mDatabase = database;
			}

			return result;
		}

		public Mysql.Settings settings() const {
			return mSettings;
		}

		public string stat() const {
			return mysql_stat(mHandle);
		}
	}
}

