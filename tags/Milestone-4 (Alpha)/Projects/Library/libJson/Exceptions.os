

// Library imports
import System.Exception;

// Project imports


public object InvalidTypeException implements IException {
	private string _ex;

	public void Constructor(string msg) {
		_ex = msg;
	}

	public string what() const {
		return _ex;
	}
}

