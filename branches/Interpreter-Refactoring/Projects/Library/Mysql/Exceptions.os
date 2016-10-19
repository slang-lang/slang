
import System.Exception;

public namespace Mysql {

	public object MysqlException extends Exception {
		public void MysqlException(string ex) {
			base.Exception(ex)
		}
	}

}

