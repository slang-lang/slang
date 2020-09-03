
import System.Exception;

public namespace Mysql { }

public object MysqlException const implements IException {
// Public

	public void Constructor( string ex ) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

// Private

	private string _exception const;
}

