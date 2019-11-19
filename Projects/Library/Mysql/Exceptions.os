
import System.Exception;

public namespace Mysql { }

public object MysqlException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception;
}

