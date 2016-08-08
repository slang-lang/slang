
//import System.GDI.IQuery;
import Connection;
import Debug;
import Result;
import Settings;
import System.String;

public namespace Mysql {

	public object Query /*implements System.GDI.IQuery*/ {
		private Mysql.Connection mConnection;
		private String mExecutedQuery;
		private String mPreparedQuery;
		private int mResultHandle;

		public void Query(Mysql.Connection connection ref, string queryStr = "") {
			mConnection = connection;
			mExecutedQuery = new String();
			mPreparedQuery = new String();
			mResultHandle = 0;

			prepare(queryStr);
		}

		public void ~Query() {
			print("~Query()");
			if ( mResultHandle ) {
				mysql_free_result(mResultHandle);
			}
		}

		public string ToString() const {
			return	"Query={ " +
					"prepared statement: \"" + mPreparedQuery.Value() + "\" " +
					"executed statement: \"" + mExecutedQuery.Value() + "\" " +
				"}";
		}

		public bool bind(string field, bool value) modify {
			if ( Mysql.MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }
			// replace all occurances of field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, double value) modify {
			if ( Mysql.MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }
			// replace field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, float value) modify {
			if ( Mysql.MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }
			// replace field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, int value) modify {
			if ( Mysql.MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }
			// replace field with value
			return mExecutedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, string value) modify {
			if ( Mysql.MysqlDebugMode ) { print("bind '" + field + "' with '" + value + "'"); }
			// replace field with value
			return mExecutedQuery.ReplaceAll(field, value);
		}

		public Mysql.Result execute(string queryStr = "") modify {
			Mysql.Result result;	// invalid object

			if ( queryStr != "" ) {
				assert(false);
				prepare(queryStr);
			}

			if ( Mysql.MysqlDebugMode ) {
				print(ToString());
			}

/*
			int result_handle = mysql_query(mConnection.handle(), mExecutedQuery.Value());
			if ( result_handle != 0 ) {
				result_handle = mysql_store_result(mConnection.handle());
				result = new Mysql.Result(result_handle);
			}

			return result;
*/

                        int error = mysql_query(mConnection.mHandle, queryStr);
                        if ( error != 0 ) {
                                // error while query execution
                                return result;  // return uninitialized result object
                        }

print(mConnection.ToString());

                        int handle = mysql_store_result(mConnection.mHandle);
                        return new Mysql.Result(handle);
		}

		public void prepare(string query) modify {
			mExecutedQuery.Value(query);
			mPreparedQuery.Value(query);
		}
	}
}

