
import System.Exception;

// declare 'System.Network' namespace to prevent a user defined private 'System.Network' namespace
public namespace System.Network { }

public object NotConnectedException const implements IException {
	public void Constructor(string ex) {
		_exception = ex;
	}

	public string what() const {
		return _exception;
	}

	private string _exception const;
}

