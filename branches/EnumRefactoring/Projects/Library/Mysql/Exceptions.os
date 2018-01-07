
import System.Exception;

public namespace Mysql {

	public object MysqlException implements IException {
		private string _exception;

		public void Constructor(string ex) {
			_exception = ex;
		}

		public string =operator(string none) const {
			return _exception;
		}

		public string what() const {
			return _exception;
		}
	}

}

