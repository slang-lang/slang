
//import System.GDI.IQuery;
import Connection;
import Debug;
import Result;
import System.String;

public namespace Mysql {

	public object Query /*implements System.GDI.IQuery*/ {
		private int mConnectionHandle;
		private String mExecutedQuery;
		private String mPreparedQuery;
		private int mResultHandle;

		public void Query(int connectionHandle, string queryStr = "") {
			mConnectionHandle = connectionHandle;
			mExecutedQuery = new String();
			mPreparedQuery = new String(queryStr);
			mResultHandle = 0;
		}

		public void ~Query() {
			if ( mResultHandle ) {
				mysql_free_result(mResultHandle);
			}
		}

		public string ToString() const {
			return	"Query { " +
					"prepared statement: \"" + mPreparedQuery.Value() + "\" " +
					"executed statement: \"" + mExecutedQuery.Value() + "\" " +
				"}";
		}

		public bool bind(string field, bool value) modify {
			print("bind '" + field + "' with '" + value + "'");
			// replace all occurances of field with value
			return mPreparedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, double value) modify {
			print("bind '" + field + "' with '" + value + "'");
			// replace field with value
			return mPreparedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, float value) modify {
			print("bind '" + field + "' with '" + value + "'");
			// replace field with value
			return mPreparedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, int value) modify {
			print("bind '" + field + "' with '" + value + "'");
			// replace field with value
			return mPreparedQuery.ReplaceAll(field, string value);
		}

		public bool bind(string field, string value) modify {
			print("bind '" + field + "' with '" + value + "'");
			// replace field with value
			return mPreparedQuery.ReplaceAll(field, value);
		}

		public Result execute(string query = "") modify {
			Result result;	// invalid object

			if ( query ) {
				mPreparedQuery.Value(query);
			}

			mExecutedQuery.Value(mPreparedQuery.Value());

			if ( MysqlDebugMode ) {
				writeln("mExecutedQuery = " + mExecutedQuery.Value());
			}

			int result_handle = mysql_query(mConnectionHandle, mExecutedQuery.Value());
			if ( result_handle != 0 ) {
				result_handle = mysql_store_result(mConnectionHandle);
				result = new Result(result_handle);
			}

			return result;
		}

		public void prepare(string query) modify {
			mPreparedQuery.Value(query);
		}
	}
}

