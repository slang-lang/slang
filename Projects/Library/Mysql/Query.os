
import Connection;
import Debug;
import Result;
import Settings;
import System.String;

public namespace Mysql {

	public object Query {
		private Mysql.Connection mConnection;
		private String mExecutedQuery;
		private String mPreparedQuery;
		private int mResultHandle;

		public void Constructor(Mysql.Connection connection ref, string queryStr = "") {
			mConnection = connection;
			mExecutedQuery = new String();
			mPreparedQuery = new String();
			mResultHandle = 0;

			prepare(queryStr);
		}

		public void Destructor() {
			if ( mResultHandle ) {
				mysql_free_result(mResultHandle);
			}
		}

		public bool bind(string field, bool value) modify {
			if ( MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }

			// replace all occurances of field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, double value) modify {
			if ( MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }

			// replace field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, float value) modify {
			if ( MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }

			// replace field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, int value) modify {
			if ( MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }

			// replace field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, string value) modify {
			if ( MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }

			// replace field with value
			return mExecutedQuery.ReplaceAll(field, value);
		}

		public Mysql.Result execute(string queryStr = "") modify {
			if ( queryStr != "" ) {
				assert(false);
				prepare(queryStr);
			}

			queryStr = mExecutedQuery;

			print(queryStr);

			int error = mysql_query(mConnection.mHandle, queryStr);
			if ( error ) {
					// error while query execution
				print(mysql_error(mConnection.mHandle));
				return Mysql.Result null;
			}

			int handle = mysql_store_result(mConnection.mHandle);
			return new Mysql.Result(handle);
		}

		public void prepare(string query) modify {
			mExecutedQuery = query;
			mPreparedQuery = query;

			if ( MysqlDebugMode ) { print(ToString()); }
		}
	}
}

