
import Result;

public namespace Mysql {

public object Query {

	private string mQueryString;

	public void Query(string query) {
		writeln("Query::Query(" + query + ")");

		mQueryString = query;
	}

	public void ~Query() {
		writeln("Query::~Query()");
	}

	public Result execute() const {
		return new Result();
	}
}

}

