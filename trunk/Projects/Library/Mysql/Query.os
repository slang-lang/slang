
import Connection;
import Result;

public namespace Mysql {

public object Query {
	private Connection mConnection;
	private string mExecutedString;
	private string mQueryString;
	private int mResultHandle;

	public void Query(Connection connection) {
		writeln("Query::Query()");

		mConnection = connection;
		mExecutedQuery = "";
		mQueryString = "";
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

	public void prepare(string query) modify {
		mQueryString = query;
	}

	public Result execute() const {
		writeln("mQueryString = " + mQueryString");

		mysql_query(mConnection.descriptor(), mQueryString);

		mResultHandle = mysql_store_result(mConnection.descriptor());

		Result result = new Result();

		return result;
	}
}

}

