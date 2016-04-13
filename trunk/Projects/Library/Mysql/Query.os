
import Connection;
import Result;

public namespace Mysql {

public object Query {
	private Connection mConnection;
	private string mExecutedString;
	private string mPreparedQuery;
	private int mResultHandle;

	public void Query(Connection connection) {
		writeln("Query::Query()");

		mConnection = connection;
		mExecutedQuery = "";
		mPreparedQuery = "";
		mResultHandle = 0;
	}

	public void ~Query() {
		writeln("Query::~Query()");

		if ( mResultHandle ) {
			mysql_free_result(mResultHandle);
		}
	}

	public bool bind(string field, bool value) modify {
		// replace field with value
		return false;
	}

	public bool bind(string field, double value) modify {
		// replace field with value
		return false;
	}

	public bool bind(string field, float value) modify {
		// replace field with value
		return false;
	}

	public bool bind(string field, int value) modify {
		// replace field with value
		return false;
	}

	public bool bind(string field, string value) modify {
		// replace field with value
		return false;
        }

	public bool execute(string query = "") modify {
		if ( query ) {
			mExecutedQuery = query;
		}

		writeln("mExecutedQuery = " + mExecutedQuery);
		int result = mysql_query(mConnection.descriptor(), mExecutedQuery);
		return (result == 0);
	}

	public void prepare(string query) modify {
		mPreparedQuery = query;
	}

/*
	public Result execute() const {
		writeln("mPreparedQuery = " + mPreparedQuery");

		mysql_query(mConnection.descriptor(), mPreparedQuery);

		mResultHandle = mysql_store_result(mConnection.descriptor());

		Result result = new Result();

		return result;
	}
*/
}

}

