
//import Query;
import Result;

public namespace Mysql {

	public object Connection {
		private string mDatabase;
		private int mHandle;
		private string mHostName;
		private string mPassword;
		private int mPort;
		private string mUserName;

		public void Connection() {
			writeln("Connection::Connection()");

			cleanup();
		}

		public void Connection(string hostname, int port, string user, string password, string database) {
			writeln("Connection::Connection(" + hostname + ", " + port + ", " + user + ", " + password + ", " + database +")");

			open(filename, mode);
		}

		public void ~Connection() {
			writeln("Connection::~Connection()");

			if ( mHandle != 0 ) {
				close();
			}
		}

		private void cleanup() modify {
			mDatabase = "";
			mHandle = 0;
			mHostName = "";
			mPassword = "";
			mPort = 0;
			mUserName = "";
		}

		public bool close() modify {
			print("Connection::close()");

			if ( mHandle == 0 ) {
				return false;
			}

			//int result = mysql_close(mHandle);
			mysql_close();
			int result = 1;

			cleanup();

			return (result == 0);
		}

		public int descriptor() const {
			return mHandle;
		}

		public string error() const {
			return mysql_error();
		}

		public string info() const {
			return mysql_info();
		}

		public bool isOpen() const {
			return (mHandle != 0);
		}

		public bool open(string hostname, int port, string user, string password, string database) modify {
			print("Connection::open(\"" + hostname + "\", " + port + ", \"" + user + "\", <password>, \"" + database + "\")");

			if ( mHandle != 0 ) {
				// we already have a connection handle
				throw new string("mysql descriptor still points to an open connection!");
			}

			/*mHandle =*/ mysql_real_connect(hostname, port, user, password, database);
			mHandle = 1;

			mDatabase = database;
			mHostName = hostname;
			mPassword = password;
			mPort = port;
			mUserName = user;

			return (mHandle != 0);
		}
	}
}

