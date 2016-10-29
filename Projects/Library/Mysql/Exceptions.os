
import System.Exception;

public namespace Mysql {

	public object MysqlException extends Exception {
		public void Constructor(string ex) {
			base.Constructor(ex)
		}
	}

}

