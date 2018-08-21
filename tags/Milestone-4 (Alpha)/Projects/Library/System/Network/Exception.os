
import System.Exception;

public namespace System.Network { }

public object NotConnectedException implements IException {
	private string _exception;

	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}
}

