
import Result;

public namespace Mysql {

public object Query {
	private string mExecutedString;
	private string mQueryString;

	public void Query() {
		writeln("Query::Query()");

		mExecutedQuery = "";
		mQueryString = "";
	}

	public void ~Query() {
		writeln("Query::~Query()");
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

		Result result = new Result();

		return result;
	}
}

}

